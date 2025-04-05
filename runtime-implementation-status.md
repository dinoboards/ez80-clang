# C Runtime Status

## CPM

| BDOS            | Description                         | Status                                                   |
|-----------------|-------------------------------------|----------------------------------------------------------|
|  0: P_TERMCPM   | System Reset                        | ✓ |
|  1: C_READ      | Console input                       | ✓         |
|  2: C_WRITE     | Console output                      | ✓ |
|  3 A_READ       | Auxiliary (Reader) input            | ✓ |
|  4 A_WRITE      | Auxiliary (Punch) output            | ✓ |
|  5 L_WRITE      | Printer output                      | ✓ |
|  6 C_RAWIO      | Direct console I/O                  | ✓         |
|  7 GET_IOBYTE   | Get IOBYTE                          | ✓         |
|  8 SET_IOBYTE   | Set IOBYTE                          | ✓         |
|  9 C_WRITESTR   | Output string                       | ✓ |
| 10 C_READSTR    | Buffered console input              | ✓ |
| 11 C_STAT       | Console status                      | ✓ |
| 12 S_BDOSVER    | Return version number               | ✓ |
| 13 DRV_ALLRESET | Reset discs                         | ✓ |
| 14 DRV_SET      | Select disc                         | ✓ |
| 15 F_OPEN       | Open file                           | ✓ |
| 16 F_CLOSE      | Close file                          | ✓ |
| 17 F_SFIRST     | search for first                    | ✓ |
| 18 F_SNEXT      | search for next                     | ✓ |
| 19 F_DELETE     | delete file                         | ✓ |
| 20 F_READ       | read next record                    | ✓ |
| 21 F_WRITE      | write next record                   | ✓ |
| 22 F_MAKE       | create file                         | ✓ |
| 23 F_RENAME     | Rename file                         | ✗ |
| 24 DRV_LOGINVEC | Return bitmap of logged-in drives   | ✗ |
| 25 DRV_GET      | Return current drive                | ✓ |
| 26 F_DMAOFF     | Set DMA address                     | ✓ |
| 27 DRV_ALLOCVEC | Return address of allocation map    | ✗ |
| 28 DRV_SETRO    | Software write-protect current disc | ✗ |
| 29 DRV_ROVEC    | Return bitmap of read-only drives   | ✗ |
| 30 F_ATTRIB     | set file attributes                 | ✗ |
| 31 DRV_DPB      | get DPB address                     | ✗ |
| 32 F_USERNUM    | get/set user number                 | ✓ |
| 33 F_READRAND   | Random access read record           | ✓ |
| 34 F_WRITERAND  | Random access write record          | ✓ |
| 35 F_SIZE       | Compute file size                   | ✓ |
| 36 F_RANDREC    | Update random access pointer        | ✗ |
| 37 DRV_RESET    | Selectively reset disc drives       | ✗ |
| 40 F_WRITEZF    | Write random with zero fill         | ✗ |

## CRT

|  Description                         | Status                                                    |
|--------------------------------------|-----------------------------------------------------------|
| Command Line arguments               | ✓          |
| Redirection                          | ✗  |
| exit                                 | ✓          |
| atexit                               | ✓          |
| _bbitrev                             | ✓  |
| _bctlz                               | ✓  |
| _bdivs                               | ✓  |
| _bdivu                               | ✓  |
| _bmulu                               | ✓  |
| _bpopcnt                             | ✓  |
| _brems                               | ✓  |
| _bremu                               | ✓  |
| _bshl                                | ✓  |
| _bshrs                               | ✓  |
| _bshru                               | ✓  |
| _dadd                                | N/A  |
| _dcmp                                | N/A  |
| _ddiv                                | N/A  |
| _dmul                                | N/A  |
| _dneg                                | N/A  |
| _drem                                | N/A  |
| _dsub                                | N/A  |
| _dtof                                | N/A  |
| _dtol                                | ✓ (as float) |
| _dtoll                               | ✓ (as float) |
| _dtoul                               | ✓ (as float) |
| _dtoull                              | ✓ (as float) |
| _fabs                                | ✓  |
| _fabsf                               | ✓  |
| _fadd                                | ✓  |
| _fcmp                                | ✓  |
| _fdiv                                | ✓  |
| _fmul                                | ✓  |
| _fneg                                | ✓  |
| _frameset                            | ✓  |
| _frameset0                           | ✓  |
| _frem                                | ✗  |
| _fsub                                | ✓  |
| _ftod                                | N/A  |
| _ftol                                | ✓  |
| _ftoll                               | ✓  |
| _ftoul                               | ✓  |
| _ftoull                              | ✓  |
| _i48and                              | ✓  |
| _i48bitrev                           | ✓  |
| _i48bswap                            | ✓  |
| _i48cmps                             | ✓  |
| _i48cmpu                             | ✓  |
| _i48cmpzero                          | ✓  |
| _i48ctlz                             | ✓  |
| _i48divs                             | ✓  |
| _i48divu                             | ✓  |
| _i48dvrmu                            | ✓  |
| _i48mulu                             | ✓  |
| _i48neg                              | ✓  |
| _i48not                              | ✓  |
| _i48or                               | ✓  |
| _i48popcnt                           | ✓  |
| _i48rems                             | ✓  |
| _i48remu                             | ✓  |
| _i48shl                              | ✓  |
| _i48shrs                             | ✓  |
| _i48shru                             | ✓  |
| _i48xor                              | ✓  |
| _iand                                | ✓  |
| _ibitrev                             | ✓  |
| _icmpzero                            | ✓  |
| _ictlz                               | ✓  |
| _idivs                               | ✓  |
| _idivu                               | ✓  |
| _idvrmu                              | ✓  |
| _imul_b                              | ✓  |
| _imulu                               | ✓  |
| _ineg                                | ✓  |
| _inot                                | ✓  |
| _ior                                 | ✓  |
| _ipopcnt                             | ✓  |
| _irems                               | ✓  |
| _iremu                               | ✓  |
| _ishl                                | ✓  |
| _ishl_b                              | ✓  |
| _ishrs                               | ✓  |
| _ishrs_b                             | ✓  |
| _ishru                               | ✓  |
| _ishru_b                             | ✓  |
| _itol                                | ✓  |
| _ixor                                | ✓  |
| _ladd                                | ✓  |
| _ladd_b                              | ✓  |
| _land                                | ✓  |
| _lbitrev                             | ✓  |
| _lbswap                              | ✓  |
| _lcmps                               | ✓  |
| _lcmpu                               | ✓  |
| _lcmpzero                            | ✓  |
| _lctlz                               | ✓  |
| _ldivs                               | ✓  |
| _ldivu                               | ✓  |
| _ldvrmu                              | ✓  |
| _lladd                               | ✓  |
| _lland                               | ✓  |
| _llbitrev                            | ✓  |
| _llbswap                             | ✓  |
| _llcmps                              | ✓  |
| _llcmpu                              | ✓  |
| _llcmpzero                           | ✓  |
| _llctlz                              | ✓  |
| _lldivs                              | ✓  |
| _lldivu                              | ✓  |
| _llmulu                              | ✓  |
| _llneg                               | ✓  |
| _llnot                               | ✓  |
| _llor                                | ✓  |
| _llpopcnt                            | ✓  |
| _llrems                              | ✓  |
| _llremu                              | ✓  |
| _llshl                               | ✓  |
| _llshrs                              | ✓  |
| _llshru                              | ✓  |
| _llsub                               | ✓  |
| _lltod                               | ✓  |
| _lltof                               | ✓  |
| _llxor                               | ✓  |
| _lmulu                               | ✓  |
| _lneg                                | ✓  |
| _lnot                                | ✓  |
| _lor                                 | ✓  |
| _lpopcnt                             | ✓  |
| _lrems                               | ✓  |
| _lremu                               | ✓  |
| _lshl                                | ✓  |
| _lshrs                               | ✓  |
| _lshru                               | ✓  |
| _lsub                                | ✓  |
| _ltod                                | ✓  |
| _ltof                                | ✓  |
| _lxor                                | ✓  |
| _sand                                | ✓  |
| _sbitrev                             | ✓  |
| _scmpzero                            | ✓  |
| _sctlz                               | ✓  |
| _sdivs                               | ✓  |
| _sdivu                               | ✓  |
| _setflag                             | ✓  |
| _smulu                               | ✓  |
| _sneg                                | ✓  |
| _snot                                | ✓  |
| _sor                                 | ✓  |
| _spopcnt                             | ✓  |
| _srems                               | ✓  |
| _sremu                               | ✓  |
| _sshl                                | ✓  |
| _sshl_b                              | ✓  |
| _sshrs                               | ✓  |
| _sshrs_b                             | ✓  |
| _sshru                               | ✓  |
| _sshru_b                             | ✓  |
| _stoi                                | ✓  |
| _stoiu                               | ✓  |
| _sxor                                | ✓  |
| _ulltod                              | ✓  |
| _ulltof                              | ✓  |
| _ultod                               | ✓  |
| _ultof                               | ✓  |

## LIBC

|  Function     | Status                                                    |
|---------------|-----------------------------------------------------------|
| abort         | ✓ |
| abs           | ✓ |
| acos          | ✓ |
| asin          | ✓ |
| atan          | ✓ |
| atan2         | ✓ |
| atexit        | ✓ |
| calloc        | ✓ |
| ceil          | ✓ |
| clearerr      | ✗ |
| clock         | ✗ |
| cos           | ✓  |
| cosh          | ✓ |
| difftime      | ✗ |
| div           | ✓ |
| errno         | ✓  |
| exit          | ✓ |
| exp           | ✓ |
| fabs          | ✓ |
| fclose        | ✓ |
| ferror        | ✓ |
| fflush        | ✗ |
| fgetc         | ✓  |
| fgets         | ✓  |
| floor         | ✓ |
| fmod          | ✓ |
| fopen         | ✓ |
| fprintf       | ✓  |
| fputc         | ✓  |
| fread         | ✓ |
| free          | ✓ |
| frexp         | ✓  |
| fseek         | ✓ |
| ftell         | ✓ |
| fwrite        | ✓ |
| getchar       | ✓  |
| getenv        | ✗ |
| getopt        | ✓  |
| gmtime        | ✗ |
| isalnum       | ✓ |
| isalpha       | ✓ |
| iscntrl       | ✓ |
| isdigit       | ✓  |
| isgraph       | ✓ |
| islower       | ✓  |
| isprint       | ✓  |
| ispunct       | ✓  |
| isspace       | ✓  |
| isupper       | ✓ |
| isxdigit      | ✓  |
| labs          | ✓ |
| ldiv          | ✓ |
| localtime     | ✗ |
| log           | ✓ |
| log10         | ✓ |
| malloc        | ✓ |
| memchr        | ✓ |
| memcmp        | ✗ |
| memcpy        | ✓ |
| memmove       | ✓ |
| memset        | ✓ |
| mktime        | ✗ |
| modf          | ✓ |
| perror        | ✓ (limited) |
| pow           | ✓ |
| printf        | ✓  |
| putchar       | ✓  |
| puts          | ✓  |
| raise         | N/A |
| rand          | ✓  |
| random        | ✓  |
| realloc       | ✓ |
| rewind        | ✗ |
| setbuf        | ✗ |
| setvbuf       | ✗ |
| sigaction     | ✗ |
| signal        | ✗ |
| sigpending    | ✗ |
| sigprocmask   | ✗ |
| sigsuspend    | ✗ |
| sigwait       | ✗ |
| sin           | ✓  |
| sinh          | ✓ |
| snprintf      | ✓  |
| sprintf       | ✓  |
| sqrt          | ✓ |
| srand         | ✓  |
| sscanf        | ✓  |
| strcat        | ✓ |
| strchr        | ✓  |
| strcmp        | ✓  |
| strcpy        | ✓  |
| strerror      | ✓ |
| strftime      | ✗ |
| strlen        | ✓  |
| strncat       | ✓ |
| strncmp       | ✓ |
| strncpy       | ✓ |
| strod         | ✓  |
| strol         | ✓  |
| strrchr       | ✓ |
| strstr        | ✓ |
| strtok        | ✓ |
| strtoll       | ✓  |
| strtoul       | ✓  |
| tanh          | ✓ |
| time          | ✗ |
| tolower       | ✓  |
| totoull       | ✓  |
| toupper       | ✓  |
| vfprintf      | ✓  |
| vprint        | ✓  |



## V99X8

|  Description                         | Status                                                    |
|--------------------------------------|-----------------------------------------------------------|
| vdp_clear_all_memory                 | ✓          |
| vdp_set_palette                      | ✓          |
| vdp_set_mode(6)                      | ✓          |
| vdp_set_mode(7)                      | ✓          |
| vdp_set_page                         | ✓          |
| vdp_out_reg_int16                    | ✓          |
| vdp_reg_write                        | ✓          |
| vdp_get_status                       | ✓          |
| vdp_cmd_wait_completion              | ✓          |
| vdp_cmd                              | ✓          |
| vdp_draw_line                        | ✓          |
