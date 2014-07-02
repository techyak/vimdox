#ifndef LIB_TECHYAK_MODES_UTILITIES_h
	#define LIB_TECHYAK_MODES_UTILITIES_h

#include <stdbool.h>
#include <stdint.h>

//debug functions
void __debug_it(int which);
void __debug_num(uint8_t num);
//end debug functions

//keycode sending functions
void __do_delay(void);

void __do_send(uint8_t key, uint8_t mod);

//end keycode sending functions

//utility functions
void __go_beginning_of_line(bool select);
void __go_end_of_line(bool select);
void __go_soft_beginning_of_lineNONScrivener(void);
void __go_soft_beginning_of_line(void);
void __do_select_all_word(void);
void __do_copy_selection(void);
void __do_delete_backwards(void);
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
//end utility functions

#endif