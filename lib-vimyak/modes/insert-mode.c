#include <util/delay.h>
#include "./insert-mode.h"
#include "./mode-utilities.h"
#include "../vimyak.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"


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

    //this is an attempt to get VIM results from searching
    //which is constantly messed up by not finding the result
    //that you searched for. This approach we disregard the CR
    //and then send an escape key to remove the find window
    //then we do a "find next" on the text that was entered
    case _INSERT_MODE_RESET_BUT_DISREGARD_CR:
    if (key == KEY_ReturnEnter) {
      set_clear_buffer();
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
      
  		case KEY_F21:
      switch (mod) {
        case _NO_MOD:
        _command_handler(&_do_command_option_alt_f);
        _set_state(_INSERT_MODE_RESET_AFTER_RETURN);
        _NOTHING
    
        default:
        _NOTHING_RESET
      }
      
      
  		case KEY_F23:
      switch (mod) {
        case _NO_MOD:
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
