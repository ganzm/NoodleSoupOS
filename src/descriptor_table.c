#include "descriptor_table.h"
#include "io.h"


#define FLAG_Gr      0x8000
#define FLAG_Sz      0x4000


#define FLAG_PRESENT 0x90
#define FLAG_PRIV3   0x60
#define FLAG_PRIV0   0x00
#define FLAG_EX      0x08
#define FLAG_DC      0x04
#define FLAG_RW      0x02

static uint64_t gdt_table[5];
static gdt_descriptor_t descriptor;


static uint64_t
create_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0
 
	return descriptor;
}

void gdt_init(){
	
	// needs to be 0
	gdt_table[0] = create_descriptor(0, 0, 0);
	
	// Code
	gdt_table[1] = create_descriptor(0, 0xFFFFFFFF, FLAG_Gr | FLAG_PRESENT | FLAG_EX | FLAG_PRIV0 | FLAG_Sz);
	gdt_table[2] = create_descriptor(0, 0, 0);
	gdt_table[3] = create_descriptor(0, 0, 0);
	gdt_table[4] = create_descriptor(0, 0xFFFFFFFF, FLAG_Gr | FLAG_PRESENT | FLAG_RW | FLAG_PRIV0 | FLAG_Sz);
	
	
	descriptor.address = (uint32_t)&gdt_table;
	descriptor.size = sizeof(gdt_table);
	
	init_gdt_asm(&descriptor);
	
}
