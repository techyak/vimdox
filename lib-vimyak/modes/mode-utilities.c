#include <util/delay.h>
#include "./mode-utilities.h"
#include "../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../lib/key-functions/public.h"
#include "../../main.h"
#include "./visual-mode.h"
#include "./normal-mode.h"
#include "./insert-mode.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"


//debug functions
/*
void __debug_it(int which)
{
  int local_key;
  int local_modifier;
  
  local_key = 0;
  local_modifier = 0;
  
  switch (which) {
    case 1:
    local_key = KEY_a_A;
    break;
    case 2:
    local_key = KEY_b_B;
    break;
    case 3:
    local_key = KEY_c_C;
    break;
    case 4:
    local_key = KEY_d_D;
    break;
    case 5:
    local_key = KEY_e_E;
    break;
    case 6:
    local_key = KEY_e_E;
    break;
    case 7:
    local_key = KEY_e_E;
    break;
    case 8:
    local_key = KEY_e_E;
    break;
    case 9:
    local_key = KEY_e_E;
    break;
    case 0:
    local_key = KEY_f_F;
    break;
  }
  
	keyboard_keys[0] = local_key;
	keyboard_modifier_keys = local_modifier; 
  usb_keyboard_send();
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);
}

void __debug_num(uint8_t num) {
  int local_key;
  int local_modifier;
  
  local_modifier = 0;
  
  switch (num) {
    case 0:
    local_key = KEY_0_RightParenthesis;
    break;
    case 1:
    local_key = KEY_1_Exclamation;
    break;
    case 2:
    local_key = KEY_2_At;
    break;
    case 3:
    local_key = KEY_3_Pound;
    break;
    case 4:
    local_key = KEY_4_Dollar;
    break;
    case 5:
    local_key = KEY_5_Percent;
    break;
    case 6:
    local_key = KEY_6_Caret;
    break;
    case 7:
    local_key = KEY_7_Ampersand;
    break;
    case 8:
    local_key = KEY_8_Asterisk;
    break;
    case 9:
    local_key = KEY_9_LeftParenthesis;
    break;
    default:
    local_modifier |= (1<<1);
    local_key = KEY_Equal_Plus; 
  }
  
  
  
  //if (_repeater != 0) {
	keyboard_keys[0] = local_key;
	keyboard_modifier_keys = local_modifier; 
  usb_keyboard_send();
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);
  //}
}
*/
//end debug functions


//shared command function/vars
void _set_command_function(void(*FunctPtr)(uint8_t, uint8_t)) {
  _command_function = FunctPtr;
}

void _set_state(_STATE new_state) {
  if (_exit_function != 0) {
    (_exit_function)();
    _exit_function = 0;
  }
  
  set_keyboard_state(new_state);
  switch (new_state) {
    case _NORMAL_MODE:
    normal_mode_setup(); 
    _NOTHING
    case _VISUAL_MODE_LINE:
    visual_mode_line_setup();
    _NOTHING
    case _VISUAL_MODE_CHAR:
    visual_mode_char_setup();
    _NOTHING      
  }
}

void _do_command_reset(void) {
  _set_state(_NORMAL_MODE);
}
//end shared command functions/vars

//repeater functions
uint8_t _repeater;

void _repeater_addition(uint8_t adder) {
  _repeater = (_repeater * 10) + adder;
  if (_repeater > 20) { _repeater = 20; } //maybe change later, but this is a safety valve...
}
void _reset_repeater(void) {
  _repeater = 0;
}
uint8_t _get_repeater(void) {
  return _repeater;
}
//end repeater functions


//keycode sending functions
void __do_delay(void) {
	_delay_ms(MAKEFILE_DEBOUNCE_TIME);
}

void __do_send(uint8_t key, uint8_t mod)
{
  keyboard_keys[0] = key;
	keyboard_modifier_keys = mod; 
	usb_keyboard_send();
  _delay_ms(MAKEFILE_DEBOUNCE_TIME);
  
  keyboard_keys[0] = 0;
	keyboard_modifier_keys = 0;
}

//end keycode sending functions

//utility functions
uint8_t my_modifiers;

void __go_beginning_of_line(bool select){
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_LeftArrow, my_modifiers);
}

void __go_end_of_line(bool select){
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_RightArrow, my_modifiers);
}

void __go_soft_beginning_of_lineNONScrivener(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<0);
  my_modifiers |= (1<<3);
  __do_send(KEY_F13, my_modifiers);  
}

void __go_soft_beginning_of_line(void) {
  __go_beginning_of_line(false);
}

void __do_select_all_word(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<2);
  __do_send(KEY_F13, my_modifiers);
}

void __do_copy_selection(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_c_C, my_modifiers);
}

void __do_paste(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_v_V, my_modifiers);  
}

void __do_delete_backwards(void) {
  my_modifiers = 0;
  __do_send(KEY_DeleteBackspace, my_modifiers);  
}

void __do_set_mark(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<0);
  __do_send(KEY_F13, my_modifiers);
  
}

void __do_swap_with_mark(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<0);
  my_modifiers |= (1<<1);
  __do_send(KEY_F13, my_modifiers);  
}

void __do_select_line(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  my_modifiers |= (1<<2);
  __do_send(KEY_F13, my_modifiers);    
}

void __do_up(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_UpArrow, my_modifiers);   
}

void __do_down(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_DownArrow, my_modifiers);    
}

void __do_left(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_LeftArrow, my_modifiers);    
}

void __do_right(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_RightArrow, my_modifiers);    
}

void __do_left_word(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  my_modifiers |= (1<<2);
  __do_send(KEY_LeftArrow, my_modifiers);    
}

void __do_right_word(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  my_modifiers |= (1<<2);
  __do_send(KEY_RightArrow, my_modifiers);    
}

void __do_scroll_up(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<2);
  my_modifiers |= (1<<3);
  __do_send(KEY_F13, my_modifiers);    
}

void __do_scroll_down(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<0);
  my_modifiers |= (1<<1);  
  my_modifiers |= (1<<2);
  __do_send(KEY_F13, my_modifiers);    
}

void __do_insert_space(void) {
  __do_send(KEY_Spacebar, 0);
}

void __go_page_down(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  my_modifiers |= (1<<2);  
  my_modifiers |= (1<<3);  
  __do_send(KEY_F13, my_modifiers);
}
void __go_page_up(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  my_modifiers |= (1<<3);  
  __do_send(KEY_F13, my_modifiers);
}

void __go_scroll_page_down(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_PageDown, my_modifiers);  
}
void __go_scroll_page_up(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_PageUp, my_modifiers);
}


void __go_end_of_file(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_End, my_modifiers);
}

void __go_beginning_of_file(bool select) {
  my_modifiers = 0;
  if (select) {
    my_modifiers |= (1<<1);
  }
  __do_send(KEY_Home, my_modifiers);  
}


void __do_select_all_file(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_a_A, my_modifiers);
}
//end utility functions


//shared recipes

//f23
void _do_command_space(uint8_t repeater) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	__do_send(KEY_Spacebar, my_modifiers);	 
}

//end shared recipes


//repeat command function
#define _CMD_ARRAY_LENGTH 20
uint8_t _cmd_array[_CMD_ARRAY_LENGTH][2];
uint8_t _cmd_array_index;

void _reset_repeat(void) {
  for (uint8_t i=0; i<_CMD_ARRAY_LENGTH; i++) {
    _cmd_array[i][0] = 0;
    _cmd_array[i][1] = 0;    
  }
  _cmd_array_index = 0;
}

void _add_command(uint8_t key, uint8_t mod) {
  _cmd_array[_cmd_array_index][0] = key;
  _cmd_array[_cmd_array_index][1] = mod;  
  _cmd_array_index++;
}

void _do_repeat(void) {
  for (uint8_t i=0; i<6; i++) {
    keyboard_keys_temp[i] = 0;
  }
  
  for (uint8_t i=0; i<_cmd_array_index; i++) {
    keyboard_keys_temp[0] = _cmd_array[i][0];
    keyboard_modifier_keys_temp = _cmd_array[i][1]; 
    vimyak_keyhandler();
    __do_send(0,0);
  }
}
//end repeat command functions