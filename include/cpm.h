#ifndef __CPMCALLS
#define __CPMCALLS

#include <stdint.h>

#define MBASE_CONST_VARIABLE(T, c) (*(T)(((uint24_t)cpm_mbase | c)))

typedef char (*CPM_FCB_t)[];
#define CPM_FCB    MBASE_CONST_VARIABLE(CPM_FCB_t, 0x005C)
#define CPM_DMABUF MBASE_CONST_VARIABLE(CPM_FCB_t, 0x0080) /* Default DMA buffer address */

// assigned to the start of the 64k CPM page (0x030000)
extern void const *const cpm_mbase;

/* Call the bdos with register pair BC set to bc and DE set
to de. The value returned in register A is the return
value. */
extern uint8_t bdos(uint16_t bc, uint16_t de);

extern void cpm_term(void);

/* Return a character without echoing if one is waiting; zero if none is
 * available. */
extern uint8_t cpm_rawio(void);

extern uint8_t cpm_read(void);

#endif
