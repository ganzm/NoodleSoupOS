#include "interrupt.h"
#include "io.h"
#include "debug.h"


#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)


static idt_entry_t idt_table[256];




/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
 
#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */
 
/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
static void int_PIC_remap(int offset1, int offset2) {
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}


void interrupt_handler() {
	LOG_DEBUG("TODO interrupt_handlern");
}

void int_IRQ_set_mask(uint8_t irq_line) {
    uint16_t port;
    uint8_t value;
 
    if(irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) | (1 << irq_line);
    outb(port, value);        
}
 
void int_IRQ_clear_mask(uint8_t irq_line) {
    uint16_t port;
    uint8_t value;
 
    if(irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) & ~(1 << irq_line);
    outb(port, value);        
}



static void idt_entry_init(idt_entry_t *entry, uint32_t handler_addr){
	
	entry->offset_low =  handler_addr         & 0xffff;
	entry->offset_high = (handler_addr >> 16) & 0xffff;
	entry->segment_selector = 0x08;
	
	// https://wiki.osdev.org/Interrupt_Descriptor_Table
	// P|DPL | S | TYPE | unused
	// 1|00    0   1110   0000 0000
	entry->some_flags = 0x8E00;
}

void int_init() {
	
	
	//idt_entry_init(&idt_table[1], (uint32_t)some_handler);
	
	//idt_entry_init(&idt_table[0x10], (uint32_t)some_handler);
	
	//idt_entry_init(&idt_table[0x20], (uint32_t)some_handler0);
	idt_entry_init(&idt_table[41], (uint32_t)interrupt_handler_41);
	
	/*
	idt_entry_init(&idt_table[0x22], (uint32_t)some_handler2);
	idt_entry_init(&idt_table[0x23], (uint32_t)some_handler3);
	idt_entry_init(&idt_table[0x24], (uint32_t)some_handler4);
	idt_entry_init(&idt_table[0x25], (uint32_t)some_handler5);
	idt_entry_init(&idt_table[0x26], (uint32_t)some_handler6);
	idt_entry_init(&idt_table[0x27], (uint32_t)some_handler7);
	*/
	
	/*
	idt_entry_init(&idt_table[0x30], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x31], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x32], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x33], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x34], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x35], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x36], (uint32_t)some_handler);
	idt_entry_init(&idt_table[0x37], (uint32_t)some_handler);
	*/
	
	// clutter together a Interupt Descritpro table descriptor
	uint8_t idt_descriptor[6];
	*(uint16_t*)idt_descriptor = sizeof(idt_table);
	*(uint32_t*)(idt_descriptor+2) = (uint32_t)idt_table;
	
	
	int_init_asm(idt_descriptor);	
	
	
	int_PIC_remap(40, 50);
	
	// enable keyboard interrupts
	int_IRQ_set_mask(0); 	 // -- no timer
	int_IRQ_clear_mask(1);
	int_IRQ_clear_mask(2);
	int_IRQ_clear_mask(3);
	int_IRQ_clear_mask(4);
	int_IRQ_clear_mask(5);
	int_IRQ_clear_mask(6);
	int_IRQ_clear_mask(7);
}
