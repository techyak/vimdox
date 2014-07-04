#include <util/delay.h>
#include "./visual-mode.h"
#include "./mode-utilities.h"
#include "../vimyak.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"

int _visual_mode_line_count;

void _visual_mode_reset(void) {
  _visual_mode_line_count = 0;
}

//visual mode char 
void _empty_char_command(uint8_t key, uint8_t mod) {
	switch (key) {
  }
  
}

void visual_mode_char_loop(uint8_t key, uint8_t mod) {
  (*_command_function)(key, mod);  
}

void visual_mode_char_setup(void) {
  _command_function = &_empty_char_command;
}
//end visual mode char 

//visual mode line 
void _empty_line_command(uint8_t key, uint8_t mod) {
	switch (key) {
    case KEY_j_J:
    _visual_mode_line_count--;
    __do_down(true);
    if (_visual_mode_line_count == 0) {
      __do_send(0,0);
      __do_swap_with_mark();
      __do_send(0,0);
      __do_set_mark();
      __do_send(0,0);      
      __do_select_line();      
    }
    else {
      set_repeatable_modified_key();   
    }
    _NOTHING
    
    case KEY_k_K:
    _visual_mode_line_count++;
    __do_up(true);
    if (_visual_mode_line_count == 0) {
      __do_send(0,0);
      __do_swap_with_mark();
      __do_send(0,0);
      __do_set_mark();
      __do_send(0,0);      
      __do_select_line();
    }
    else {
      set_repeatable_modified_key();   
    }    
    _NOTHING    
      
    case KEY_d_D:
    __do_copy_selection();
    __do_delete_backwards();
    __do_swap_with_mark();
    _set_state(_NORMAL_MODE);
    _NOTHING
    
    case KEY_c_C:
    __do_copy_selection();
    __do_delete_backwards();
    __do_swap_with_mark();
    _set_state(_INSERT_MODE);    
    _NOTHING    
  
    case KEY_y_Y:
    __do_copy_selection();
    __do_swap_with_mark();
    _set_state(_NORMAL_MODE);    
    _NOTHING    
  }
}

void visual_mode_line_loop(uint8_t key, uint8_t mod) { 
  (*_command_function)(key, mod);      
}

void visual_mode_line_setup(void) {
  _visual_mode_line_count = 0;
  __do_set_mark(); 
  __do_send(0,0);
  __do_select_line();  
  _command_function = &_empty_line_command;
}
//end visual mode line 