#!/bin/bash

# process/scan the first 2 input files and identify relocating address
# output file is $1 plus a relocation table appended.

file1=$1
file2=$2
output_file=$3

# check if both files exist
if [[ ! -f "$file1" || ! -f "$file2" ]]; then
  echo "Both input files must exist."
  exit 1
fi

# check if both files are the same length
size1=$(stat -c%s "$file1")
size2=$(stat -c%s "$file2")

if [[ $size1 -ne $size2 ]]; then
  echo "Input files must be the same length."
  exit 1
fi

# The output file is identical to the first file, plus the relocation data append to the end
cp "$file1" "$output_file"

#get the start address of the relocation tabler
relocation_table_start=$(stat -c%s "$output_file")

relocation_count=0

# read the entire files into memory
mapfile -t bytes1 < <(xxd -p -c 1 "$file1")
mapfile -t bytes2 < <(xxd -p -c 1 "$file2")

# loop through each byte and find the different bytes
for ((i=0; i<size1; i++)); do
  if [[ "${bytes1[i]}" != "${bytes2[i]}" ]]; then
    # check if the difference is exactly 2
    diff=$((0x${bytes2[i]} - 0x${bytes1[i]}))
    if [[ $diff -ne 0x20 ]]; then
      echo "Error: Byte difference at position $i is not 0x20."
      echo $diff, ${bytes1[i]}, ${bytes2[i]}
      exit 1
    fi
    # convert the address to 24-bit and write to the output file in LSB first
    printf "%06x" $i | tac -rs .. | xxd -r -p >> "$output_file"
    ((relocation_count++))
  fi
done

# calculate the padding needed to align to 128-byte page boundary
output_size=$(stat -c%s "$output_file")
padding=$((128 - ((output_size + 6) % 128)))
if [[ $padding -ne 128 ]]; then
  dd if=/dev/zero bs=1 count=$padding oflag=append conv=notrunc status=none >> "$output_file"
fi

# write the number of relocated bytes to the output file in LSB first
printf "%06x" $relocation_count | tac -rs .. | xxd -r -p >> "$output_file"

# write the 24-bit address of the start of the relocation table in LSB first
printf "%06x" $relocation_table_start | tac -rs .. | xxd -r -p >> "$output_file"

