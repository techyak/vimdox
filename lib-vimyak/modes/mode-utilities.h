#ifndef LIB_TECHYAK_MODES_UTILITIES_h
	#define LIB_TECHYAK_MODES_UTILITIES_h

#include <stdbool.h>
#include <stdint.h>
#include "../vimyak.h"

//debug functions
//void __debug_it(int which);
//void __debug_num(uint8_t num);
//end debug functions

//keycode sending functions
void __do_delay(void);
void __do_send(uint8_t key, uint8_t mod);
//end keycode sending functions

//shared command function/vars
void (*_command_function)(uint8_t, uint8_t);
void _set_command_function(void(*FunctPtr)(uint8_t, uint8_t));
void _set_state(_STATE new_state);
void _do_command_reset(void);
void (*_exit_function)(void);
//end shared command functions/vars

//repeater functions
void _repeater_addition(uint8_t adder);
void _reset_repeater(void);
uint8_t _get_repeater(void);
//end repeater functions

//utility functions
void __go_beginning_of_line(bool select);
void __go_end_of_line(bool select);
void __go_soft_beginning_of_lineNONScrivener(void);
void __go_soft_beginning_of_line(void);
void __do_select_all_word(void);
void __do_copy_selection(void);
void __do_paste(void);
void __do_delete_backwards(void);
void __do_delete_forward(void);
void __do_set_mark(void);
void __do_swap_with_mark(void);
void __do_select_line(void);
void __do_up(bool select);
void __do_down(bool select);
void __do_left(bool select);
void __do_right(bool select);
void __do_left_word(bool select);
void __do_right_word(bool select);
void __do_scroll_up(void);
void __do_scroll_down(void);
void __do_insert_space(void);
void __go_page_down(void);
void __go_page_up(void);
void __go_scroll_page_down(bool select);
void __go_scroll_page_up(bool select);
void __go_end_of_file(bool select);
void __go_beginning_of_file(bool select);
void __do_select_all_file(void); 
void __do_find_forward(void);
void __do_find_backward(void);
//end utility functions

//shared recipes
void _do_command_space(uint8_t repeater); //f23
void _do_command_option_alt_f(uint8_t repeater); //f21
void _do_command_alt_f(uint8_t repeater); //shift f24
void _do_command_dash(uint8_t repeater);
//end shared recipes

//repeat command function - under construction
void _reset_repeat(void); 
void _add_command(uint8_t key, uint8_t mod);
void _do_repeat(void);
//end repeat command functions

#define _NOTHING return; break;
#define _NOTHING_RESET _do_command_reset(); return; break;
#endif