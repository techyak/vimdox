#ifndef LIB_VIMYAK_MODE_INSERT_h
	#define LIB_VIMYAK_MODE_INSERT_h

	#include <stdbool.h>
	#include <stdint.h>

/*
void _insert_mode_reset(void);
void insert_mode_reset_and_cr_after_single_char_loop(uint8_t key, uint8_t mod);
void insert_mode_reset_and_cr_after_single_char_setup(void);  

void insert_mode_reset_after_single_char_loop(uint8_t key, uint8_t mod);
void insert_mode_reset_after_single_char_loop(void);  
  
void insert_mode_reset_after_return_loop(uint8_t key, uint8_t mod);
void insert_mode_reset_after_return_setup(void);  
void insert_mode_setup(void);  
*/

void insert_mode_loop(uint8_t key, uint8_t mod);
#endif