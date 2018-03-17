#include "string.h"

size_t strlen(const char *str) {
	const char *tmp = str;
	while(  *(tmp++) != '\0');
	
	return tmp - str;
}
