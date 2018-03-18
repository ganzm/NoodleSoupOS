#include "inttypes.h"
#include "fb.h"
#include "serial.h"
#include "io.h"
#include "descriptor_table.h"
#include "debug.h"


void os_main() {

	

	LOG_INIT();

	fb_clear();
	
	fb_set_color(FG_CYAN, BG_BLACK_BLINK);
	fb_write("----------\n");
	fb_set_color(FG_GREEN, BG_BLACK);
	fb_write("NoodSoupOS\n");
	fb_set_color(FG_CYAN, BG_BLACK_BLINK);
	fb_write("----------\n");
	fb_set_color(FG_GREEN, BG_BLACK);
	
	
	
	init_gdt();
	fb_write("GDT initialized\n");
	
	LOG_DEBUG("hello log\n");

	


	fb_write("Now Ready!\n");
	/*
	fb_move_cursor(0x0051);
	for(int i = 0 ; i < 100; i++) {
		fb_write("0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789\r\ntest", 137);
	}
	*/	
	
}
