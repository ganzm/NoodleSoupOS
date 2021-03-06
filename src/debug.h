#ifndef DEBUG_H
#define DEBUG_H

#define LOG_INIT()     debug_init()
#define LOG_DEBUG(str) debug_write(str)


void debug_init();

void debug_write(const char* str);

#endif /* DEBUG_H */
