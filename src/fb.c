#include "fb.h"
#include "io.h"


#define SCREEN_LENGTH 80
#define SCREEN_HEIGTH 25

/** positions of the cursor */
static uint16_t cursor_pos = 0;

/** Current foreground/background color high byte=bg, low byte=fg */
static uint16_t color = ((BG_BLACK & 0xf) << 4) | (FG_GREEN & 0xf);


void fb_set_color(unsigned char fg, unsigned char bg) {
	color = ((bg & 0xf) << 4) | (fg & 0xf);
}
	

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param pos  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(uint pos, char c, unsigned char fg, unsigned char bg) {
	uint16_t *fb= (uint16_t *)0x000B8000;
	uint16_t tmp = ((bg & 0x0F) << 12) | ((fg & 0x0f) << 8) | c;
	fb[pos] = tmp;
}

 void fb_write_cell_current_color(uint pos, char c) {
	uint16_t *fb= (uint16_t *)0x000B8000;
	fb[pos] = (color << 8) | c;
}


/**
 * Moves the cursor of the framebuffer to the given position
 */
void fb_move_cursor(uint16_t pos) {
	outb(0x3D4, 14);    // 14 tells the framebuffer to expect the highest 8 bits of the position
    outb(0x3D5, ((pos >> 8) & 0xff));  //sending the highest 8 bits of pos
    outb(0x3D4, 15);    // 15 tells the framebuffer to expect the lowest 8 bits of the position
    outb(0x3D5, pos & 0xff);  //sending the lowest 8 bits of pos
    
    cursor_pos = pos;
}


int fb_write(const char *buf) {

	for(uint i = 0; 1; i++){
		char c = buf[i];
		if(c == '\0') {
			// end of string
			break;
		}

		if(0x20 <= c && c <= 0x7e) {
			// write single VISIBLE char to current cursor position
			fb_write_cell_current_color(cursor_pos, c);
		}
		
		// move cursor
		if(c == '\n'){
			// move cursor to next line
			cursor_pos = cursor_pos - (cursor_pos % SCREEN_LENGTH) + SCREEN_LENGTH;
			
			fb_move_cursor(cursor_pos);
		}
		else if(c == '\r'){
			cursor_pos = cursor_pos - (cursor_pos % SCREEN_LENGTH);
		}
		else {
			// advance cursor
			fb_move_cursor(++cursor_pos);
		}
		
		
		// scroll if cursor is out of bounds
		while(cursor_pos >= (SCREEN_LENGTH * SCREEN_HEIGTH)) {
			
			uint16_t *fb= (uint16_t *)0x000B8000;
			for(int j = 0; j < ((SCREEN_LENGTH * SCREEN_HEIGTH) - SCREEN_LENGTH); j++) {
				fb[j] = fb[j+SCREEN_LENGTH];
			}
			
			// Clear last line
			for(int j = ((SCREEN_LENGTH * SCREEN_HEIGTH) - SCREEN_LENGTH);
				j < (SCREEN_LENGTH * SCREEN_HEIGTH); 
				j++) {
					
				fb[j] = 0;
			}
			
			
			// move cursor one line up
			cursor_pos -= SCREEN_LENGTH;
			fb_move_cursor(cursor_pos);
		}
	}
	
	return 0;
}


void fb_clear() {
	uint16_t *fb= (uint16_t *)0x000B8000;	
	
	for(uint i = 0 ; i < (SCREEN_LENGTH * SCREEN_HEIGTH) ; i++) {
		fb[i] = 0;
	}
	
	fb_move_cursor(0);
}
