
# Ansi C implementation of io functions

These functions are to be implemented for cp/m 2.0 and up.

There are, as best can be achieved, designed to comply with ANSI C standard.

Standard File I/O Operations in ANSI C
ANSI C provides a set of standard file I/O operations, which include:

# File Operations

- `fopen`: Open a file.
- `fclose`: Close a file.
- `fread`: Read from a file.
- `fwrite`: Write to a file.
- `fseek`: Move the file pointer to a specific location.
- `ftell`: Get the current file pointer position.
- `rewind`: Reset the file pointer to the beginning of the file.
- `fflush`: Flush the output buffer to the file.
- `fgetc`: Get a character from a file.
- `fputc`: Write a character to a file.
- `fgets`: Get a string from a file.
- `fputs`: Write a string to a file.
- `fprintf`: Write formatted output to a file.
- `fscanf`: Read formatted input from a file.
- `feof`: Check if the end of the file has been reached.
- `ferror`: Check for a file error.
- `clearerr`: Clear the error and end-of-file indicators for a file.

# Standard Streams

- `stdin`: Standard input stream.
- `stdout`: Standard output stream.
- `stderr`: Standard error stream.

# Implementation Details for CP/M Platform

To make these functions functional on the CP/M platform, the following steps need to be taken:

## File Operations

- `fopen`: Implement using `cpm_f_open` and `cpm_f_make` to handle file opening and creation. Map ANSI C modes to CP/M file operations.
- `fclose`: Implement using `cpm_f_close` to close the file and write any pending data.
- `fread`: Implement using `cpm_f_readrand` to read data from the file.
- `fwrite`: Implement using `cpm_f_writerand` to write data to the file.
- `fseek`: Implement to move the file pointer using CP/M file operations.
- `ftell`: Implement to return the current file pointer position.
- `rewind`: Implement to reset the file pointer to the beginning of the file.
- `fflush`: Implement to flush the output buffer to the file.
- `fgetc`: Implement to get a character from the file.
- `fputc`: Implement to write a character to the file.
- `fgets`: Implement to get a string from the file.
- `fputs`: Implement to write a string to the file.
- `fprintf`: Implement to write formatted output to the file.
- `fscanf`: Implement to read formatted input from the file.
- `feof`: Implement to check if the end of the file has been reached.
- `ferror`: Implement to check for a file error.
- `clearerr`: Implement to clear the error and end-of-file indicators for a file.
