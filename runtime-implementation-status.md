# C Runtime Status

## CPM

| BDOS            | Description                         | Status                                                   |
|-----------------|-------------------------------------|----------------------------------------------------------|
|  0: P_TERMCPM   | System Reset                        | <span class="implemented"/> |
|  1: C_READ      | Console input                       | <span class="implemented"/>         |
|  2: C_WRITE     | Console output                      | <span class="implemented"/> |
|  3 A_READ       | Auxiliary (Reader) input            | <span class="implemented"/> |
|  4 A_WRITE      | Auxiliary (Punch) output            | <span class="implemented"/> |
|  5 L_WRITE      | Printer output                      | <span class="implemented"/> |
|  6  C_RAWIO     | Direct console I/O                  | <span class="implemented"/>         |
|  7 GET_IOBYTE   | Get IOBYTE                          | <span class="implemented"/>         |
|  8 SET_IOBYTE   | Set IOBYTE                          | <span class="implemented"/>         |
|  9 C_WRITESTR   | Output string                       | <span class="implemented"/> |
| 10 C_READSTR    | Buffered console input              | <span class="not-implemented"/> |
| 11 C_STAT       | Console status                      | <span class="not-implemented"/> |
| 12 S_BDOSVER    | Return version number               | <span class="not-implemented"/> |
| 13 DRV_ALLRESET | Reset discs                         | <span class="not-implemented"/> |
| 14 DRV_SET      | Select disc                         | <span class="not-implemented"/> |
| 15 F_OPEN       | Open file                           | <span class="not-implemented"/> |
| 16 F_CLOSE      | Close file                          | <span class="not-implemented"/> |
| 17 F_SFIRST     | search for first                    | <span class="not-implemented"/> |
| 18 F_SNEXT      | search for next                     | <span class="not-implemented"/> |
| 19 F_DELETE     | delete file                         | <span class="not-implemented"/> |
| 20 F_READ       | read next record                    | <span class="not-implemented"/> |
| 21 F_WRITE      | write next record                   | <span class="not-implemented"/> |
| 22 F_MAKE       | create file                         | <span class="not-implemented"/> |
| 23 F_RENAME     | Rename file                         | <span class="not-implemented"/> |
| 24 DRV_LOGINVEC | Return bitmap of logged-in drives   | <span class="not-implemented"/> |
| 25 DRV_GET      | Return current drive                | <span class="not-implemented"/> |
| 26 F_DMAOFF     | Set DMA address                     | <span class="not-implemented"/> |
| 27 DRV_ALLOCVEC | Return address of allocation map    | <span class="not-implemented"/> |
| 28 DRV_SETRO    | Software write-protect current disc | <span class="not-implemented"/> |
| 29 DRV_ROVEC    | Return bitmap of read-only drives   | <span class="not-implemented"/> |
| 30 F_ATTRIB     | set file attributes                 | <span class="not-implemented"/> |
| 31 DRV_DPB      | get DPB address                     | <span class="not-implemented"/> |
| 32 F_USERNUM    | get/set user number                 | <span class="not-implemented"/> |
| 33 F_READRAND   | Random access read record           | <span class="not-implemented"/> |
| 34 F_WRITERAND  | Random access write record          | <span class="not-implemented"/> |
| 35 F_SIZE       | Compute file size                   | <span class="not-implemented"/> |
| 36 F_RANDREC    | Update random access pointer        | <span class="not-implemented"/> |
| 37 DRV_RESET    | Selectively reset disc drives       | <span class="not-implemented"/> |
| 40 F_WRITEZF    | Write random with zero fill         | <span class="not-implemented"/> |

## CRT

|  Description                         | Status                                                    |
|--------------------------------------|-----------------------------------------------------------|
| Command Line arguments               | <span class="implemented"/>          |
| Redirection                          | <span class="not-implemented"/>  |
| exit                                 | <span class="implemented"/>          |
| atexit                               | <span class="implemented"/>          |
| _bbitrev      | <span class="implemented"/>  |
| _bctlz        | <span class="implemented"/>  |
| _bdivs        | <span class="implemented"/>  |
| _bdivu        | <span class="implemented"/>  |
| _bmulu        | <span class="implemented"/>  |
| _bpopcnt      | <span class="implemented"/>  |
| _brems        | <span class="implemented"/>  |
| _bremu        | <span class="implemented"/>  |
| _bshl         | <span class="implemented"/>  |
| _bshrs        | <span class="implemented"/>  |
| _bshru        | <span class="implemented"/>  |
| _dadd         | <span class="na"/>  |
| _dcmp         | <span class="na"/>  |
| _ddiv         | <span class="na"/>  |
| _dmul         | <span class="na"/>  |
| _dneg         | <span class="na"/>  |
| _drem         | <span class="na"/>  |
| _dsub         | <span class="na"/>  |
| _dtof         | <span class="na"/>  |
| _dtol         | <span class="implemented"/> (as float) |
| _dtoll        | <span class="implemented"/> (as float) |
| _dtoul        | <span class="implemented"/> (as float) |
| _dtoull       | <span class="implemented"/> (as float) |
| _fabs         | <span class="implemented"/>  |
| _fabsf        | <span class="implemented"/>  |
| _fadd         | <span class="implemented"/>  |
| _fcmp         | <span class="implemented"/>  |
| _fdiv         | <span class="implemented"/>  |
| _fmul         | <span class="implemented"/>  |
| _fneg         | <span class="implemented"/>  |
| _frameset     | <span class="implemented"/>  |
| _frameset0    | <span class="implemented"/>  |
| _frem         | <span class="not-implemented"/>  |
| _fsub         | <span class="implemented"/>  |
| _ftod         | <span class="na"/>  |
| _ftol         | <span class="implemented"/>  |
| _ftoll        | <span class="implemented"/>  |
| _ftoul        | <span class="implemented"/>  |
| _ftoull       | <span class="implemented"/>  |
| _i48and       | <span class="implemented"/>  |
| _i48bitrev    | <span class="implemented"/>  |
| _i48bswap     | <span class="implemented"/>  |
| _i48cmps      | <span class="implemented"/>  |
| _i48cmpu      | <span class="implemented"/>  |
| _i48cmpzero   | <span class="implemented"/>  |
| _i48ctlz      | <span class="implemented"/>  |
| _i48divs      | <span class="implemented"/>  |
| _i48divu      | <span class="implemented"/>  |
| _i48dvrmu     | <span class="implemented"/>  |
| _i48mulu      | <span class="implemented"/>  |
| _i48neg       | <span class="implemented"/>  |
| _i48not       | <span class="implemented"/>  |
| _i48or        | <span class="implemented"/>  |
| _i48popcnt    | <span class="implemented"/>  |
| _i48rems      | <span class="implemented"/>  |
| _i48remu      | <span class="implemented"/>  |
| _i48shl       | <span class="implemented"/>  |
| _i48shrs      | <span class="implemented"/>  |
| _i48shru      | <span class="implemented"/>  |
| _i48xor       | <span class="implemented"/>  |
| _iand         | <span class="implemented"/>  |
| _ibitrev      | <span class="implemented"/>  |
| _icmpzero     | <span class="implemented"/>  |
| _ictlz        | <span class="implemented"/>  |
| _idivs        | <span class="implemented"/>  |
| _idivu        | <span class="implemented"/>  |
| _idvrmu       | <span class="implemented"/>  |
| _imul_b       | <span class="implemented"/>  |
| _imulu        | <span class="implemented"/>  |
| _ineg         | <span class="implemented"/>  |
| _inot         | <span class="implemented"/>  |
| _ior          | <span class="implemented"/>  |
| _ipopcnt      | <span class="implemented"/>  |
| _irems        | <span class="implemented"/>  |
| _iremu        | <span class="implemented"/>  |
| _ishl         | <span class="implemented"/>  |
| _ishl_b       | <span class="implemented"/>  |
| _ishrs        | <span class="implemented"/>  |
| _ishrs_b      | <span class="implemented"/>  |
| _ishru        | <span class="implemented"/>  |
| _ishru_b      | <span class="implemented"/>  |
| _itol         | <span class="implemented"/>  |
| _ixor         | <span class="implemented"/>  |
| _ladd         | <span class="implemented"/>  |
| _ladd_b       | <span class="implemented"/>  |
| _land         | <span class="implemented"/>  |
| _lbitrev      | <span class="implemented"/>  |
| _lbswap       | <span class="implemented"/>  |
| _lcmps        | <span class="implemented"/>  |
| _lcmpu        | <span class="implemented"/>  |
| _lcmpzero     | <span class="implemented"/>  |
| _lctlz        | <span class="implemented"/>  |
| _ldivs        | <span class="implemented"/>  |
| _ldivu        | <span class="implemented"/>  |
| _ldvrmu       | <span class="implemented"/>  |
| _lladd        | <span class="implemented"/>  |
| _lland        | <span class="implemented"/>  |
| _llbitrev     | <span class="implemented"/>  |
| _llbswap      | <span class="implemented"/>  |
| _llcmps       | <span class="implemented"/>  |
| _llcmpu       | <span class="implemented"/>  |
| _llcmpzero    | <span class="implemented"/>  |
| _llctlz       | <span class="implemented"/>  |
| _lldivs       | <span class="implemented"/>  |
| _lldivu       | <span class="implemented"/>  |
| _llmulu       | <span class="implemented"/>  |
| _llneg        | <span class="implemented"/>  |
| _llnot        | <span class="implemented"/>  |
| _llor         | <span class="implemented"/>  |
| _llpopcnt     | <span class="implemented"/>  |
| _llrems       | <span class="implemented"/>  |
| _llremu       | <span class="implemented"/>  |
| _llshl        | <span class="implemented"/>  |
| _llshrs       | <span class="implemented"/>  |
| _llshru       | <span class="implemented"/>  |
| _llsub        | <span class="implemented"/>  |
| _lltod        | <span class="implemented"/>  |
| _lltof        | <span class="implemented"/>  |
| _llxor        | <span class="implemented"/>  |
| _lmulu        | <span class="implemented"/>  |
| _lneg         | <span class="implemented"/>  |
| _lnot         | <span class="implemented"/>  |
| _lor          | <span class="implemented"/>  |
| _lpopcnt      | <span class="implemented"/>  |
| _lrems        | <span class="implemented"/>  |
| _lremu        | <span class="implemented"/>  |
| _lshl         | <span class="implemented"/>  |
| _lshrs        | <span class="implemented"/>  |
| _lshru        | <span class="implemented"/>  |
| _lsub         | <span class="implemented"/>  |
| _ltod         | <span class="implemented"/>  |
| _ltof         | <span class="implemented"/>  |
| _lxor         | <span class="implemented"/>  |
| _sand         | <span class="implemented"/>  |
| _sbitrev      | <span class="implemented"/>  |
| _scmpzero     | <span class="implemented"/>  |
| _sctlz        | <span class="implemented"/>  |
| _sdivs        | <span class="implemented"/>  |
| _sdivu        | <span class="implemented"/>  |
| _setflag      | <span class="implemented"/>  |
| _smulu        | <span class="implemented"/>  |
| _sneg         | <span class="not-implemented"/>  |
| _snot         | <span class="implemented"/>  |
| _sor          | <span class="implemented"/>  |
| _spopcnt      | <span class="not-implemented"/>  |
| _srems        | <span class="not-implemented"/>  |
| _sremu        | <span class="implemented"/>  |
| _sshl         | <span class="not-implemented"/>  |
| _sshl_b       | <span class="not-implemented"/>  |
| _sshrs        | <span class="not-implemented"/>  |
| _sshrs_b      | <span class="not-implemented"/>  |
| _sshru        | <span class="not-implemented"/>  |
| _sshru_b      | <span class="not-implemented"/>  |
| _stoi         | <span class="not-implemented"/>  |
| _stoiu        | <span class="not-implemented"/>  |
| _sxor         | <span class="not-implemented"/>  |
| _ulltod       | <span class="not-implemented"/>  |
| _ulltof       | <span class="not-implemented"/>  |
| _ultod        | <span class="implemented"/>  |
| _ultof        | <span class="implemented"/>  |

## LIBC

|  Function     | Status                                                    |
|---------------|-----------------------------------------------------------|
| abort         | <span class="not-implemented"/> |
| abs           | <span class="not-implemented"/> |
| acos          | <span class="not-implemented"/> |
| asin          | <span class="not-implemented"/> |
| atan          | <span class="not-implemented"/> |
| atan2         | <span class="not-implemented"/> |
| atexit        | <span class="not-implemented"/> |
| calloc        | <span class="implemented"/> |
| ceil          | <span class="not-implemented"/> |
| clearerr      | <span class="not-implemented"/> |
| clock         | <span class="not-implemented"/> |
| cos           | <span class="implemented"/>  |
| cosh          | <span class="not-implemented"/> |
| difftime      | <span class="not-implemented"/> |
| div           | <span class="not-implemented"/> |
| errno         | <span class="implemented"/>  |
| exit          | <span class="not-implemented"/> |
| exp           | <span class="not-implemented"/> |
| fabs          | <span class="not-implemented"/> |
| fclose        | <span class="not-implemented"/> |
| ferror        | <span class="not-implemented"/> |
| fflush        | <span class="not-implemented"/> |
| fgetc         | <span class="implemented"/>  |
| fgets         | <span class="implemented"/>  |
| floor         | <span class="not-implemented"/> |
| fmod          | <span class="implemented"/> |
| fmod          | <span class="not-implemented"/> |
| fopen         | <span class="not-implemented"/> |
| fprintf       | <span class="implemented"/>  |
| fputc         | <span class="implemented"/>  |
| fread         | <span class="not-implemented"/> |
| free          | <span class="implemented"/> |
| frexp         | <span class="implemented"/>  |
| fseek         | <span class="not-implemented"/> |
| ftell         | <span class="not-implemented"/> |
| fwrite        | <span class="not-implemented"/> |
| getchar       | <span class="implemented"/>  |
| getenv        | <span class="not-implemented"/> |
| getopt        | <span class="implemented"/>  |
| gmtime        | <span class="not-implemented"/> |
| isalnum       | <span class="not-implemented"/> |
| isalpha       | <span class="not-implemented"/> |
| iscntrl       | <span class="not-implemented"/> |
| isdigit       | <span class="implemented"/>  |
| isgraph       | <span class="not-implemented"/> |
| islower       | <span class="implemented"/>  |
| isprint       | <span class="implemented"/>  |
| ispunct       | <span class="implemented"/>  |
| isspace       | <span class="implemented"/>  |
| isupper       | <span class="not-implemented"/> |
| isxdigit      | <span class="implemented"/>  |
| labs          | <span class="not-implemented"/> |
| ldiv          | <span class="not-implemented"/> |
| localtime     | <span class="not-implemented"/> |
| log           | <span class="not-implemented"/> |
| log10         | <span class="not-implemented"/> |
| malloc        | <span class="implemented"/> |
| memcmp        | <span class="not-implemented"/> |
| memcpy        | <span class="not-implemented"/> |
| memmove       | <span class="not-implemented"/> |
| memset        | <span class="not-implemented"/> |
| mktime        | <span class="not-implemented"/> |
| modf          | <span class="not-implemented"/> |
| perror        | <span class="not-implemented"/> |
| pow           | <span class="not-implemented"/> |
| printf        | <span class="implemented"/>  |
| putchar       | <span class="implemented"/>  |
| puts          | <span class="implemented"/>  |
| raise         | <span class="not-implemented"/> |
| rand          | <span class="implemented"/>  |
| random        | <span class="implemented"/>  |
| realloc       | <span class="implemented"/> |
| rewind        | <span class="not-implemented"/> |
| setbuf        | <span class="not-implemented"/> |
| setvbuf       | <span class="not-implemented"/> |
| sigaction     | <span class="not-implemented"/> |
| signal        | <span class="not-implemented"/> |
| sigpending    | <span class="not-implemented"/> |
| sigprocmask   | <span class="not-implemented"/> |
| sigsuspend    | <span class="not-implemented"/> |
| sigwait       | <span class="not-implemented"/> |
| sin           | <span class="implemented"/>  |
| sinh          | <span class="not-implemented"/> |
| snprintf      | <span class="implemented"/>  |
| sprintf       | <span class="implemented"/>  |
| sqrt          | <span class="not-implemented"/> |
| srand         | <span class="implemented"/>  |
| sscanf        | <span class="implemented"/>  |
| strcat        | <span class="not-implemented"/> |
| strchr        | <span class="implemented"/>  |
| strcmp        | <span class="implemented"/>  |
| strcpy        | <span class="implemented"/>  |
| strerror      | <span class="not-implemented"/> |
| strftime      | <span class="not-implemented"/> |
| strlen        | <span class="implemented"/>  |
| strncat       | <span class="not-implemented"/> |
| strncmp       | <span class="not-implemented"/> |
| strncpy       | <span class="not-implemented"/> |
| strod         | <span class="implemented"/>  |
| strol         | <span class="implemented"/>  |
| strrchr       | <span class="not-implemented"/> |
| strstr        | <span class="not-implemented"/> |
| strtok        | <span class="not-implemented"/> |
| strtoll       | <span class="implemented"/>  |
| strtoul       | <span class="implemented"/>  |
| system        | <span class="not-implemented"/> |
| tanh          | <span class="not-implemented"/> |
| time          | <span class="not-implemented"/> |
| tolower       | <span class="implemented"/>  |
| totoull       | <span class="implemented"/>  |
| toupper       | <span class="implemented"/>  |
| vfprintf      | <span class="implemented"/>  |
| vprint        | <span class="implemented"/>  |





## V99X8

|  Description                         | Status                                                    |
|--------------------------------------|-----------------------------------------------------------|
| vdp_clear_all_memory                 | <span class="implemented"/>          |
| vdp_set_palette                      | <span class="implemented"/>          |
| vdp_set_mode(6)                      | <span class="implemented"/>          |
| vdp_set_mode(7)                      | <span class="implemented"/>          |
| vdp_set_page                         | <span class="implemented"/>          |
| vdp_out_reg_int16                    | <span class="implemented"/>          |
| vdp_reg_write                        | <span class="implemented"/>          |
| vdp_get_status                       | <span class="implemented"/>          |
| vdp_cmd_wait_completion              | <span class="implemented"/>          |
| vdp_cmd                              | <span class="implemented"/>          |
| vdp_draw_line                        | <span class="implemented"/>          |

<style>
.implemented {
  padding: 1px 2px 3px 2px;
  border-radius: 3px;
  color: white;
  font-size: 0.9em;
  background-color: green;
}
.implemented::before {
  content: 'implemented';

}
.not-implemented {
  padding: 1px 2px 3px 2px;
  border-radius: 3px;
  color: white;
  font-size: 0.9em;
  background-color: grey;
}
.not-implemented::before {
  content: 'not implemented'
}

.na {
  padding: 1px 2px 3px 2px;
  border-radius: 3px;
  color: grey;
  font-size: 0.9em;
  background-color: darkgrey;
}
.na::before {
  content: 'n/a'
}
</style>
