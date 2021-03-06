#include "inttypes.h"

void io_wait();

/**
 * outb - send a byte to an I/O port
 */
void outb(uint16_t io_port, uint8_t value);


/** inb:
 *  Read a byte from an I/O port.
 *
 *  @param  io_port The address of the I/O port
 *  @return      The read byte
 */
uint8_t inb(uint16_t io_port);



// TODO should be moved
void init_gdt_asm(void *descriptor);
void int_init_asm(void *descriptor);
