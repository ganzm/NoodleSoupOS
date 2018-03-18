#include "debug.h"
#include "serial.h"


void debug_init() {
	// Setup COM1 for debugging
	serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
	serial_configure_line(SERIAL_COM1_BASE);
}


void debug_write(const char* str){
	char c;
	while((c=*(str++)) != '\0'){
		serial_send(SERIAL_COM1_BASE, c);
	}
}
