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
| _i48divs      | <span class="not-implemented"/>  |
| _i48divu      | <span class="not-implemented"/>  |
| _i48dvrmu     | <span class="not-implemented"/>  |
| _i48mulu      | <span class="not-implemented"/>  |
| _i48neg       | <span class="not-implemented"/>  |
| _i48not       | <span class="not-implemented"/>  |
| _i48or        | <span class="not-implemented"/>  |
| _i48popcnt    | <span class="not-implemented"/>  |
| _i48rems      | <span class="not-implemented"/>  |
| _i48remu      | <span class="not-implemented"/>  |
| _i48shl       | <span class="not-implemented"/>  |
| _i48shrs      | <span class="not-implemented"/>  |
| _i48shru      | <span class="not-implemented"/>  |
| _i48xor       | <span class="not-implemented"/>  |
| _iand         | <span class="implemented"/>  |
| _ibitrev      | <span class="not-implemented"/>  |
| _icmpzero     | <span class="not-implemented"/>  |
| _ictlz        | <span class="not-implemented"/>  |
| _idivs        | <span class="implemented"/>  |
| _idivu        | <span class="not-implemented"/>  |
| _idvrmu       | <span class="implemented"/>  |
| _imul_b       | <span class="not-implemented"/>  |
| _imulu        | <span class="implemented"/>  |
| _ineg         | <span class="implemented"/>  |
| _inot         | <span class="implemented"/>  |
| _ior          | <span class="implemented"/>  |
| _ipopcnt      | <span class="not-implemented"/>  |
| _irems        | <span class="implemented"/>  |
| _iremu        | <span class="implemented"/>  |
| _ishl         | <span class="implemented"/>  |
| _ishl_b       | <span class="not-implemented"/>  |
| _ishrs        | <span class="implemented"/>  |
| _ishrs_b      | <span class="not-implemented"/>  |
| _ishru        | <span class="implemented"/>  |
| _ishru_b      | <span class="not-implemented"/>  |
| _itol         | <span class="not-implemented"/>  |
| _ixor         | <span class="implemented"/>  |
| _ladd         | <span class="implemented"/>  |
| _ladd_b       | <span class="not-implemented"/>  |
| _land         | <span class="implemented"/>  |
| _lbitrev      | <span class="not-implemented"/>  |
| _lbswap       | <span class="not-implemented"/>  |
| _lcmps        | <span class="implemented"/>  |
| _lcmpu        | <span class="implemented"/>  |
| _lcmpzero     | <span class="not-implemented"/>  |
| _lctlz        | <span class="implemented"/>  |
| _ldivs        | <span class="implemented"/>  |
| _ldivu        | <span class="implemented"/>  |
| _ldvrmu       | <span class="implemented"/>  |
| _lladd        | <span class="implemented"/>  |
| _lland        | <span class="not-implemented"/>  |
| _llbitrev     | <span class="not-implemented"/>  |
| _llbswap      | <span class="not-implemented"/>  |
| _llcmps       | <span class="not-implemented"/>  |
| _llcmpu       | <span class="implemented"/>  |
| _llcmpzero    | <span class="implemented"/>  |
| _llctlz       | <span class="implemented"/>  |
| _lldivs       | <span class="implemented"/>  |
| _lldivu       | <span class="implemented"/>  |
| _llmulu       | <span class="implemented"/>  |
| _llneg        | <span class="implemented"/>  |
| _llnot        | <span class="not-implemented"/>  |
| _llor         | <span class="not-implemented"/>  |
| _llpopcnt     | <span class="not-implemented"/>  |
| _llrems       | <span class="implemented"/>  |
| _llremu       | <span class="implemented"/>  |
| _llshl        | <span class="implemented"/>  |
| _llshrs       | <span class="not-implemented"/>  |
| _llshru       | <span class="not-implemented"/>  |
| _llsub        | <span class="implemented"/>  |
| _lltod        | <span class="not-implemented"/>  |
| _lltof        | <span class="not-implemented"/>  |
| _llxor        | <span class="not-implemented"/>  |
| _lmulu        | <span class="implemented"/>  |
| _lneg         | <span class="implemented"/>  |
| _lnot         | <span class="not-implemented"/>  |
| _lor          | <span class="implemented"/>  |
| _lpopcnt      | <span class="not-implemented"/>  |
| _lrems        | <span class="not-implemented"/>  |
| _lremu        | <span class="not-implemented"/>  |
| _lshl         | <span class="implemented"/>  |
| _lshrs        | <span class="implemented"/>  |
| _lshru        | <span class="not-implemented"/>  |
| _lsub         | <span class="implemented"/>  |
| _ltod         | <span class="implemented"/>  |
| _ltof         | <span class="implemented"/>  |
| _lxor         | <span class="implemented"/>  |
| _sand         | <span class="implemented"/>  |
| _sbitrev      | <span class="not-implemented"/>  |
| _scmpzero     | <span class="not-implemented"/>  |
| _sctlz        | <span class="not-implemented"/>  |
| _sdivs        | <span class="implemented"/>  |
| _sdivu        | <span class="not-implemented"/>  |
| _setflag      | <span class="implemented"/>  |
| _smulu        | <span class="not-implemented"/>  |
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
| cos           | <span class="implemented"/>  |
| errno         | <span class="implemented"/>  |
| fgetc         | <span class="implemented"/>  |
| fgets         | <span class="implemented"/>  |
| fmod          | <span class="implemented"/> |
| fprintf       | <span class="implemented"/>  |
| fputc         | <span class="implemented"/>  |
| frexp         | <span class="implemented"/>  |
| getchar       | <span class="implemented"/>  |
| getopt        | <span class="implemented"/>  |
| isdigit       | <span class="implemented"/>  |
| islower       | <span class="implemented"/>  |
| isprint       | <span class="implemented"/>  |
| ispunct       | <span class="implemented"/>  |
| isspace       | <span class="implemented"/>  |
| isxdigit      | <span class="implemented"/>  |
| printf        | <span class="implemented"/>  |
| putchar       | <span class="implemented"/>  |
| puts          | <span class="implemented"/>  |
| rand          | <span class="implemented"/>  |
| random        | <span class="implemented"/>  |
| sin           | <span class="implemented"/>  |
| snprintf      | <span class="implemented"/>  |
| sprintf       | <span class="implemented"/>  |
| srand         | <span class="implemented"/>  |
| sscanf        | <span class="implemented"/>  |
| strchr        | <span class="implemented"/>  |
| strcmp        | <span class="implemented"/>  |
| strcpy        | <span class="implemented"/>  |
| strlen        | <span class="implemented"/>  |
| strod         | <span class="implemented"/>  |
| strol         | <span class="implemented"/>  |
| strtoll       | <span class="implemented"/>  |
| strtoul       | <span class="implemented"/>  |
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
