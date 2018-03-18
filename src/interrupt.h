#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "inttypes.h"

/**
 * Interrupt Descriptor Table entry
 */
typedef struct idt_entry {
	
	uint16_t offset_low;		// offset bits 0..15
	uint16_t segment_selector;
	uint16_t some_flags;
	uint16_t offset_high;		// offset bits 16..31
	
} __attribute__ ((packed)) idt_entry_t;


void int_init();


extern void interrupt_handler_41();

void interrupt_handler();

#endif /* INTERRUPT_H */

