#ifndef __CPMCALLS
#define __CPMCALLS

#include <stdint.h>

/* Return a character without echoing if one is waiting; zero if none is
 * available. */
extern uint8_t cpm_rawio(void);

extern uint8_t cpm_read(void);

#endif
