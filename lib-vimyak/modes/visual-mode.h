#ifndef LIB_VIMYAK_MODE_VISUAL_h
	#define LIB_VIMYAK_MODE_VISUAL_h

	#include <stdbool.h>
	#include <stdint.h>

void _visual_mode_reset(void);

void visual_mode_line_loop(uint8_t key, uint8_t mod);
void visual_mode_char_loop(uint8_t key, uint8_t mod);
void visual_mode_line_setup(void);
void visual_mode_char_setup(void);
  
#endif
