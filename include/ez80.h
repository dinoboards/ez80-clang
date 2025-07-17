#ifndef __EZ80_H
#define __EZ80_H

#include <stdint.h>

extern uint24_t __attribute__((pure)) get_address_in_base(const uint16_t a);

/*
 *_port_out() - Output a byte to an I/O port
 * @port: the PORT_IO variable to be assigned
 * @value: the byte to be written to the port
 *
 * equivalent to port = value;
 * (uses a common function to avoid code duplication)
 *
 */
#define port_out(port, value) _port_out(((((uint24_t)port)) << 8) + ((uint24_t)(value)))
extern void _port_out(const uint24_t data);

/* The address space for eZ80's I/O 64k PORT addresses */
#define IO_SPACE __attribute__((address_space(3)))

/* I/O PORT definition for eZ80
 * The following defines a uint8_t VDP_ADDR constant
 * such that reads/writes will be translated to appropriate
 * eZ80 in/out instructions.
 */
#define PORT_IO(c) (*((volatile uint8_t IO_SPACE *)((uint24_t)c)))

#define DI __asm__("DI")
#define EI __asm__("EI")

extern uint8_t _heap[];
extern void   *_get_spl();
extern void   *_get_sps();

typedef uint16_t near_ptr_t;
#define AS_NEAR_PTR(x) (near_ptr_t)(uint24_t)(x)

/**
 * @brief Extracts the near 16-bit pointer from the 24-bit address.
 *
 * This function extracts the near 16-bit pointer from the given 24-bit address.
 * It checks if the 24-bit address is within the same 64k page as the MBASE.
 * If not, it prints an error message and aborts.
 *
 * @param[in] address The 24-bit address to be used.
 * @param[in] mbase The base address of the 64k page.
 * @param[in] file The name of the file where the function is called from.
 * @param[in] line The line number in the file where the function is called from.
 *
 * @return The near 16-bit pointer extracted from the 24-bit address.
 */
extern near_ptr_t as_near_ptr_safe(const void *address, const uint8_t mbase, const char *file, const int line);

/**
 * @hide
 * @brief storage modifier to place variable in the eZ80's on-chip RAM.
 *
 * The variable will be initialised to 0.
 *
 */
#define __bss_on_chip __attribute__((section(".bss_on_chip")))

/**
 * @hide
 * @brief storage modifier to place variable in the eZ80's on-chip RAM.
 *
 * The variable will be initialised as specified.
 *
 */
#define __data_on_chip __attribute__((section(".data_on_chip")))

/*
 * @hide
 * @brief function modifier to copy function into the eZ80's on-chip RAM
 * and then execute from there
 */
#define __func_on_chip __attribute__((section(".text_on_chip")))

/**
 * @brief Get the application's allocated memory
 *
 * For a standard COM application, the address returned is the MBASE address (eg: 0x030000)
 * For an EXE application, the start extended memory address the application was loaded into. (eg: 0x200000)
 *
 * @return uint8_t* The starting address allocated to the application.
 */
extern uint8_t *get_memory_start();

/**
 * @brief Get the the first address after the application's allocated memory
 *
 * For standard COM application, the address returned is the MBASE+1 address (eg: 0x040000)
 * For an EXE application, the address returned is the first byte address beyond the allocated memory. eg (0x400000)
 *
 * For EXE, the top of memory is free for use.
 * For COM, the top of memory is used by CPM.
 *
 * @return uint8_t* the end address allocated to the application.
 */
extern uint8_t *get_memory_end();

#endif
