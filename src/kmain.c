#include "inttypes.h"
#include "fb.h"
#include "serial.h"
#include "io.h"


void os_main() {
	
	fb_write_cell(0, 'A', FG_WHITE, BG_BLACK);
	fb_write_cell(1, 'X', FG_BROWN, BG_GREEN_BLINK);
	
	
	fb_move_cursor(0x0051);
	
	for(int i = 0 ; i < 100; i++) {
		fb_write("0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789\r\ntest", 137);
	}
	
	
	
	// Setup COM1
	serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
	serial_configure_line(SERIAL_COM1_BASE);
	
	
	serial_send(SERIAL_COM1_BASE, 0x41);
	serial_send(SERIAL_COM1_BASE, 0x42);
	serial_send(SERIAL_COM1_BASE, 0x43);
	serial_send(SERIAL_COM1_BASE, 0x44);

}
