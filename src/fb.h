#ifndef FB_H
#define FB_H



#include "inttypes.h"


#define FG_BLACK 0x0
#define FG_BLUE 0x1
#define FG_GREEN 0x2
#define FG_CYAN 0x3
#define FG_RED 0x4
#define FG_MAGENTA 0x5
#define FG_BROWN 0x6
#define FG_LIGHTGRAY 0x7
#define FG_DARKGRAY 0x8
#define FG_LIGHTBLUE 0x9
#define FG_LIGHTGREEN 0xa
#define FG_LIGHTCYAN 0xb
#define FG_LIGHTRED 0xc
#define FG_LIGHTMAGENTA 0xd
#define FG_LIGHTBROWN 0xe
#define FG_WHITE 0xf

#define BG_BLACK 0x0
#define BG_BLUE 0x1
#define BG_GREEN 0x2
#define BG_CYAN 0x3
#define BG_RED 0x4
#define BG_MAGENTA 0x5
#define BG_BROWN 0x6
#define BG_LIGHGRAY 0x7
#define BG_BLACK_BLINK 0x8
#define BG_BLUE_BLINK 0x9
#define BG_GREEN_BLINK 0xa
#define BG_CYAN_BLINK 0xb
#define BG_RED_BLINK 0xc
#define BG_MAGENTA_BLINK 0xd
#define BG_BROWN_BLINK 0xe
#define BG_LIGHGRAY_BLINK 0xf

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void fb_move_cursor(uint16_t pos);



int fb_write(char *buf, uint len);

#endif  /* FB_H */
