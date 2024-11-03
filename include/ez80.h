#ifndef __EZ80_H
#define __EZ80_H

#include <stdint.h>

/*
 *_port_out() - Output a byte to an I/O port
 * @port: the PORT_IO variable to be assigned
 * @value: the byte to be written to the port
 *
 * equivalent to port = value;
 * (uses a common function to avoid code duplication)
 *
 */
#define port_out(port, value) _port_out(((((uint24_t)&port)) << 8) + ((uint24_t)(value)))
extern void _port_out(const uint24_t data);

/* The address space for eZ80's I/O 64k PORT addresses */
#define IO_SPACE __attribute__((address_space(3)))

/* I/O PORT definition for eZ80
 * The following defines a uint8_t VDP_ADDR constant
 * such that reads/writes will be translated to appropriate
 * eZ80 in/out instructions.
 */
#define PORT_IO(c) (*((volatile uint8_t IO_SPACE *)c))

#define DI __asm__("DI")
#define EI __asm__("EI")

#endif
