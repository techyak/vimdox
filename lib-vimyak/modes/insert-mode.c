#include <util/delay.h>
#include "./insert-mode.h"
#include "./mode-utilities.h"
#include "../vimyak.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"

/*

void insert_mode_reset_and_cr_after_single_char_loop(uint8_t key, uint8_t mod) {
  
}
void insert_mode_reset_and_cr_after_single_char_setup(void) {
  
}
 
void insert_mode_reset_after_single_char_loop(uint8_t key, uint8_t mod) {
  
}
void insert_mode_reset_after_single_char_loop(void) {
  
}
  
  
  
void insert_mode_reset_after_return_loop(uint8_t key, uint8_t mod) {
  
}
void insert_mode_reset_after_return_setup(void) {
  
}

void insert_mode__setup(void) {
  
}
*/


void insert_mode_loop(uint8_t key, uint8_t mod) {
  switch (get_keyboard_state()) {
    case _INSERT_MODE_RESET_AFTER_SINGLE_CHAR:
    __do_send(key,mod);
    __do_send(0,0);
    set_skip_further_commands();
    _set_state(_NORMAL_MODE);
    _NOTHING
      
    case _INSERT_MODE_RESET_AND_CR_AFTER_SINGLE_CHAR:
    __do_send(key,mod);
    __do_send(0,0);
    __do_send(KEY_ReturnEnter,0);
    __do_send(0,0);
    set_skip_further_commands();
    _set_state(_NORMAL_MODE);
    _NOTHING
      
    case _INSERT_MODE_RESET_AFTER_RETURN:
    if (key == KEY_ReturnEnter) {
      __do_send(key,mod);
      __do_send(0,0);
      set_skip_further_commands();
      _set_state(_NORMAL_MODE);
      _NOTHING      
    }
    
    default:
    switch (key) {
      case KEY_p_P:
      switch (mod) {
        case _L_CONTROL:
        case _R_CONTROL:
        __do_paste();         
        _NOTHING
          
          //ugly solution I hate this...
        default:
        set_repeatable_key();
        _NOTHING
      }
      
  		case KEY_F23:
      switch (mod) {
        case _NO_MOD: // /
        _do_command_space(0);
        _set_state(_INSERT_MODE_RESET_AFTER_RETURN);
        _NOTHING
    
        default:
        _NOTHING_RESET
      }      
      
      default:
      set_repeatable_key();
      _NOTHING
    }
    
  }
}
