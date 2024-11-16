#include <cpm.h>
#include <stdio.h>
#include <string.h>

// buffer must be allocated within the first 64k segment

static uint8_t buffer[SECSIZE] __attribute__((section(".startup_z80")));

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  FCB   *file_fcb    = (FCB *)stream;
  size_t total_bytes = size * nmemb;
  size_t bytes_read  = 0;

  cpm_f_dmaoff(AS_CPM_PTR(buffer));

  while (bytes_read < total_bytes) {
    // Calculate the current record and offset within the record
    unsigned long record_num = file_fcb->rwptr / SECSIZE;
    unsigned long offset     = file_fcb->rwptr % SECSIZE;

    // Read the current record
    file_fcb->ranrec = record_num;
    if (cpm_f_readrand(AS_CPM_PTR(file_fcb)) != 0) {
      break; // Error reading record
    }

    // Calculate the number of bytes to copy from the current record
    size_t bytes_to_copy = SECSIZE - offset;
    if (bytes_to_copy > total_bytes - bytes_read) {
      bytes_to_copy = total_bytes - bytes_read;
    }

    // Copy the bytes from the buffer to the destination
    memcpy((uint8_t *)ptr + bytes_read, buffer + offset, bytes_to_copy);
    bytes_read += bytes_to_copy;
    file_fcb->rwptr += bytes_to_copy;
  }

  return bytes_read / size;
}
