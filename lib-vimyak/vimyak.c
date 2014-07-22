#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>
#include "../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../lib/key-functions/public.h"
#include "../main.h"
#include "./vimyak.h"
#include "../keyboard/ergodox/controller/teensy-2-0--led.h"
#include "../keyboard/ergodox/layout/default--led-control.h"

//modes
#include "./modes/mode-utilities.h"
#include "./modes/normal-mode.h"
#include "./modes/visual-mode.h"
#include "./modes/insert-mode.h"

//keycodes for switch
#include "../lib/usb/usage-page/keyboard.h"



//I can't use escape to do the normal mode escaping as in traditional
//--VIM because escape is used for a lot of other things in the OS
//--therefore I had decided to use F24 as my escape key. Modify this if you'd like
#define _RESETKEY         KEY_F24
#define _RESETMOD         0

_STATE _keyboard_state;
_STATE _previous_state;
bool _keypress_message_sent;
bool _repeating_key;
bool _repeating_modified_key;


bool _flush_keys; 
bool _ignore_rest_of_keys;


//utility functions

_STATE get_keyboard_state(void) {
  return _keyboard_state;
}
void set_keyboard_state(_STATE new_state) { 
  _keyboard_state = new_state;
}

void set_clear_buffer(void) {
  _flush_keys = true;
}
void set_skip_further_commands(void) {
  _ignore_rest_of_keys = true;
}
void set_repeatable_key(void) {
  _repeating_key = true;
}

void set_repeatable_modified_key(void) {
  _repeating_modified_key = true;
}

void _handle_sending_of_keys(void) {
  if (_flush_keys) {
    for (uint8_t i=0; i<6; i++) {
      keyboard_keys[i] = 0;
      keyboard_keys_temp[i] = 0;
      keyboard_modifier_keys = 0;   
      keyboard_modifier_keys_temp = 0;
    }    
    usb_keyboard_send(); //need to send a blank slate if nothing is passed along
  }
  else {
    for (uint8_t i=0; i<6; i++) {
      keyboard_keys[i] = keyboard_keys_temp[i];
      keyboard_modifier_keys = keyboard_modifier_keys_temp;
    }
    usb_keyboard_send();
    for (uint8_t i=0; i<6; i++) {
      keyboard_keys[i] = 0;
      keyboard_modifier_keys = 0;
    }
  }
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);
}
//end utility functions

//LEDs
void _LEDhandler(void) {
//take care of LEDs
  if (_previous_state != _keyboard_state) {
    switch (_keyboard_state) {
      case _NORMAL_MODE:
      _kb_led_all_off();
      break;            
      
      case _VISUAL_MODE_LINE:
      case _VISUAL_MODE_CHAR:      
      _kb_led_1_set_percent(5);    
      _kb_led_1_on();
      _kb_led_3_set_percent(5);    
      _kb_led_3_on();      
      break;
      
      default:
      _kb_led_1_set_percent(5);    
      _kb_led_1_on();
      _kb_led_3_off();
      break;
    }
  }
}
//end LEDs


void _vimyak_reset(void) {
  _keyboard_state = _NORMAL_MODE;  
  _do_command_reset();
  _visual_mode_reset();
  _reset_repeater();
}

void vimyak_init(void) {
  _vimyak_reset();
  
  //NOW any pre initial-loop setup
  
}

void _key_handler(uint8_t key, uint8_t mod) {
  _repeating_key = false;
  _repeating_modified_key = false;
  
  switch (_keyboard_state) {
    case _NORMAL_MODE:
    normal_mode_loop(key, mod);
    _NOTHING
    case _INSERT_MODE:
    case _INSERT_MODE_RESET_AFTER_SINGLE_CHAR:
    case _INSERT_MODE_RESET_AND_CR_AFTER_SINGLE_CHAR:
    case _INSERT_MODE_RESET_AFTER_RETURN:
    case _INSERT_MODE_RESET_BUT_DISREGARD_CR:
    insert_mode_loop(key, mod);
    _NOTHING
    case _VISUAL_MODE_LINE:
    visual_mode_line_loop(key, mod);
    _NOTHING
    case _VISUAL_MODE_CHAR:
    visual_mode_char_loop(key, mod);
    _NOTHING      
  }  
}

void _pre_command_handler(uint8_t key, uint8_t mod) {
  //pre command handling without reference to keyboard_state
  //_add_command(key, mod);
  
  if ((key == _RESETKEY) && (mod == _RESETMOD)) {
    _vimyak_reset();
    _ignore_rest_of_keys = true;    
  }
}

void vimyak_keyhandler(void) {
  _keypress_message_sent = false;
  _previous_state = _keyboard_state;
  
  _flush_keys = false; //for commands. when a command is sent it is handled
                        //--and then the keys are removed from the keyboard_keys_temp array
  
  _ignore_rest_of_keys = false; //this is for special commands which destroy any
                                //--other keys in the keyboard_keys_temp array
                                //--while not allowing them to be processed.
  
  //a possible add-on here.
  //--if I want to allow for non-standard modifiers
  //--then there should be a function here which
  //--scans the keypress array and looks for that modifier
  //--then sets the state of a personal modifier that will
  //--then be tested in the key-by-key handling phase for
  //--each mode.
  //For now I am going to go forward without alternative
  //--modifiers as I am not sure when/how I would use them
  //--at this stage.
  
	for (uint8_t i=0; i<6; i++) {
    if (keyboard_keys_temp[i] !=0) {
     if (!_ignore_rest_of_keys)  {
        _pre_command_handler(keyboard_keys_temp[i], keyboard_modifier_keys_temp);
        _key_handler(keyboard_keys_temp[i], keyboard_modifier_keys_temp);
        if ((!_repeating_key) && (!_repeating_modified_key)) keyboard_keys_temp[i] = 0;      
      }
      else keyboard_keys_temp[i] = 0;
    }
	}
  if (!_repeating_modified_key) _handle_sending_of_keys();
  
  _LEDhandler();
}