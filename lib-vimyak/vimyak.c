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
#include "./modes/normal-mode.h"
#include "./modes/visual-mode.h"

//keycodes for switch
#include "../lib/usb/usage-page/keyboard.h"



//I can't use escape to do the normal mode escaping as in traditional
//--VIM because escape is used for a lot of other things in the OS
//--therefore I had decided to use F24 as my escape key. Modify this if you'd like
#define _RESETKEY         KEY_F24

_STATE _keyboard_state;
_STATE _previous_state;
bool _keypress_message_sent;
bool _repeating_key;


bool _flush_keys; 
bool _ignore_rest_of_keys;


//utility functions
void set_mode(_STATE mode) {
  _keyboard_state = mode;
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
/*
void _do_send(uint8_t key, uint8_t modifier)
{
  keyboard_keys[0] = key;
	keyboard_modifier_keys = modifier; 
	usb_keyboard_send();
  //_delay_ms(MAKEFILE_DEBOUNCE_TIME);
  
  _keypress_message_sent = true;
  keyboard_keys[0] = 0;
	keyboard_modifier_keys = 0;
  //usb_keyboard_send();
}
*/
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

/*
uint8_t _key_queue[6]={0,0,0,0,0,0};
uint8_t _final_key;
uint8_t _final_key_index;
uint8_t l = 0;

void _send_remaining_keys() {
  for (uint8_t i=0; i<6; i++) {
    keyboard_keys[i] = keyboard_keys_temp[i];
    keyboard_modifier_keys = keyboard_modifier_keys_temp;
  }
  usb_keyboard_send();
  for (uint8_t i=0; i<6; i++) {
    keyboard_keys[i] = 0;
    keyboard_modifier_keys = 0;
  }
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);  
}

void _register_key(uint8_t key, uint8_t index){
  _final_key = key;
  _final_key_index = index;
}
void  _get_final_key(void){
  keyboard_keys_temp[_final_key_index] = _final_key;
  _final_key = 0;
  _final_key_index = 0;
}

void _add_to_key_queue(uint8_t key, uint8_t index) {
  _key_queue[index] = key;  
}
void _flush_key_queue(void) {
	for (uint8_t i=0; i<6; i++) {
    keyboard_keys[i] = _key_queue[i];
	} 
  keyboard_modifier_keys = keyboard_modifier_keys_temp;
  
	usb_keyboard_send();
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);
  
	for (uint8_t i=0; i<6; i++) {
    keyboard_keys[i] = 0;
    _key_queue[i] = 0;
	} 
  
	keyboard_modifier_keys = 0;
}

void  _get_keys_from_queue(void) {
	for (uint8_t i=0; i<6; i++) {
    keyboard_keys_temp[i] = _key_queue[i];
    _key_queue[i] = 0;
	} 
}
*/

//end utility functions

//LEDs
void _LEDhandler(void) {
//take care of LEDs
  if (_previous_state != _keyboard_state) {
    if (_keyboard_state != _NORMAL_MODE) {
      _kb_led_1_set_percent(5);    
      _kb_led_1_on();
    }
    else { 
      _kb_led_1_off();
    }
  }
}
//end LEDs


void _vimyak_reset(void) {
  _keyboard_state = _NORMAL_MODE;  
}

void vimyak_init(void) {
  _vimyak_reset();
  
  //NOW any pre initial-loop setup
  
}

void _key_handler(uint8_t* key, uint8_t mod) {
  _repeating_key = false;
  
  switch (_keyboard_state) {
    case _NORMAL_MODE:
    normal_mode_loop(*key, mod);
    //if (*key == KEY_i_I) {
    //  _keyboard_state = _INSERT_MODE;
    //}
    break;
    case _INSERT_MODE:
    set_repeatable_key();
    //_repeating_key = true;
    break;
  }
  
  if (!_repeating_key) {
    *key = 0;
  }
}

void _pre_command_handler(uint8_t* key, uint8_t mod) {
  if (*key == _RESETKEY) {
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
        _pre_command_handler(&keyboard_keys_temp[i], keyboard_modifier_keys_temp);
        _key_handler(&keyboard_keys_temp[i], keyboard_modifier_keys_temp);      
      }
      else keyboard_keys_temp[i] = 0;
    }
	}
  _handle_sending_of_keys();
  
  _LEDhandler();
}