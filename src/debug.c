#include "debug.h"
#include "serial.h"


void debug_write(const char* str){

		char c;
		while((c=*(str++)) != '\0'){
			serial_send(SERIAL_COM1_BASE, c);
		}
}
