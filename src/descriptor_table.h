#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include "inttypes.h"

typedef struct gdt_descriptor {
	unsigned short size;
	unsigned int address;
	
} __attribute__ ((packed)) gdt_descriptor_t;


void gdt_init();

#endif /* DESCRIPTOR_TABLE_H */

