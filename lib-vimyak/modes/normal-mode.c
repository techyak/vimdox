#include <util/delay.h>
#include "./normal-mode.h"
#include "./mode-utilities.h"
#include "../vimyak.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"


void normal_mode_loop(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_i_I:
    set_mode(_INSERT_MODE);
    break;
    case KEY_j_J:
    __do_down(false);
    break;   
		
    case KEY_DeleteBackspace:
    case KEY_Spacebar:
    case KEY_DeleteForward:
    case KEY_ReturnEnter:
    case KEY_Tab:
    case KEY_Escape:
    set_repeatable_key();
    set_skip_further_commands();
    break;
    }
}

/*

//a
bool _do_append(void) {
  my_modifiers = 0;
	_do_send(KEY_RightArrow, my_modifiers);
  
  return false;
}

//A
bool _do_append_eol(void) {
	my_modifiers = 0;
	my_modifiers |=  (1<<3);
	
	_do_send(KEY_RightArrow, my_modifiers);
  
  return false;
}

//b
bool _do_previous_word(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<2);
	_do_send(KEY_LeftArrow, my_modifiers);
  
  return true;
}

//^b
bool _do_page_down(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  my_modifiers |= (1<<2);
  my_modifiers |= (1<<3);  
  _do_send(KEY_F13, my_modifiers);

  return true;
}
  

//cc
bool _do_change_line(void) {
  __go_beginning_of_line(false);
  __go_end_of_line(true);
  __do_copy_selection();
  __go_soft_beginning_of_line();
  __go_end_of_line(true);
  __do_delete_backwards();
  
  return false;
}

//caw 
bool _do_change_all_word(void) {
  __do_select_all_word();
  __do_copy_selection();
  __do_delete_backwards();
  
  return false;
}

//cw
bool _do_change_word(void) {
  __do_right_word(true);
  __do_delete_backwards();
  
  return true;
}

//daw
bool _do_delete_all_word(void) {
  __do_select_all_word();
  
  my_modifiers = 0;
  _do_send(KEY_DeleteBackspace, my_modifiers);
  return false;
}

//dd
bool _do_delete_line(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<0);
  my_modifiers |= (1<<2);
  _do_send(KEY_F13, my_modifiers);
  return false;
}

//dw
bool _do_delete_word(void) {
  __do_right_word(true);
  __do_delete_backwards();
  return false;
}

//e
bool _do_end_word(void) {
  __do_select_all_word();
  
  my_modifiers = 0;
  _do_send(KEY_RightArrow, my_modifiers);
  return false;
}

//^f
bool _do_page_up(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  my_modifiers |= (1<<3);  
  _do_send(KEY_F13, my_modifiers);

  return true;
}


//I
bool _do_insert_soft_beginning_of_line(void) {
  __go_soft_beginning_of_line();
  return false;
}

//^j
bool _do_scroll_up(void) {
  __do_scroll_up();
  return true;
}

//^k
bool _do_scroll_down(void) {
  __do_scroll_down();  
  return true;
}

//n
bool _do_next_find_forward(void) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	_do_send(KEY_g_G, my_modifiers);
  return true;
}

//N
bool _do_next_find_backward(void) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	my_modifiers |= (1<<1);
	_do_send(KEY_g_G, my_modifiers);
  return true;
}


//o
bool _do_open_line_below(void) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	_do_send(KEY_RightArrow, my_modifiers);
	
  my_modifiers = 0;
  _do_send(KEY_ReturnEnter, my_modifiers);
  return true;
}


//O
bool _do_open_line_above(void) {
	__go_soft_beginning_of_line();
	
  my_modifiers = 0;
  _do_send(KEY_ReturnEnter, my_modifiers);
  
  my_modifiers = 0;
  _do_send(KEY_UpArrow, my_modifiers);
  return true;
}

//p
bool _do_paste(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  _do_send(KEY_RightArrow, my_modifiers);
  my_modifiers = 0;
  _do_send(KEY_ReturnEnter, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  _do_send(KEY_LeftArrow, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  _do_send(KEY_v_V, my_modifiers);
  return true;
}

//P
bool _do_paste_previous_line(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  _do_send(KEY_LeftArrow, my_modifiers);
  my_modifiers = 0;
  _do_send(KEY_ReturnEnter, my_modifiers);
  my_modifiers = 0;
  _do_send(KEY_UpArrow, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  _do_send(KEY_v_V, my_modifiers);
  return true;
}

//r
bool _do_select_next_char(void) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  _do_send(KEY_RightArrow, my_modifiers);
  return false;
}

//r - exit function
bool _do_back_one_char(void) {
  my_modifiers = 0;
  _do_send(KEY_LeftArrow, my_modifiers);
  return false;
}

//s
bool _subst_char(void) {
	my_modifiers = 0;
	_do_send(KEY_DeleteForward, my_modifiers);
  return false;
}

//S
//see change_line()


//u
bool _do_undo(void) {
	my_modifiers = 0;
	my_modifiers |=  (1<<3);
	
	_do_send(KEY_z_Z, my_modifiers);
  return true;
}

//V
bool _do_visual_mode_line_exit_function(void) {
  __do_swap_with_mark();
  return false;
}

//w
bool _do_next_word(void) {
	my_modifiers = 0;
	my_modifiers |=  (1<<2);
  
  _do_send(KEY_RightArrow, my_modifiers);
  return true;
}

//yy
bool _do_copy_line(void) {
  __do_set_mark();
  __go_beginning_of_line(false);
  __go_end_of_line(true);
  __do_copy_selection();
  __do_swap_with_mark();
  
  return false;
}

//yaw 
bool _do_copy_all_word(void) {
  __do_set_mark();
  __do_select_all_word();
  __do_copy_selection();
  __do_swap_with_mark();
  
  return false;
}

//yw
bool _do_copy_word(void) {
  __do_right_word(true);
  __do_copy_selection();
  __do_left(false);
  return false;
}


//@y - my personal copy selection for mouse selected text primarily
bool _do_copy_selection(void) {
  __do_copy_selection();  
  
  return false;
}

// /
bool _do_find(void) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	_do_send(KEY_f_F, my_modifiers);
  return false;
}

//0
bool _do_hard_beginning_of_line(void) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
  _do_send(KEY_LeftArrow, my_modifiers);
  return false;
}

//^
bool _do_soft_beginning_of_line(void) {
  __go_soft_beginning_of_line();
  
  return false;
}

//$
bool _do_end_of_line(void) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	_do_send(KEY_RightArrow, my_modifiers);	
  return false;
}

//:q(enter)
bool _do_quit(void) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	_do_send(KEY_q_Q, my_modifiers);	
  return false;
}

//:x(enter)
bool _do_save(void) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	_do_send(KEY_s_S, my_modifiers);	
  return false;
}

//f23
bool _do_command_space(void) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	_do_send(KEY_Spacebar, my_modifiers);	
  return false;
}


//f21
bool _do_command_option_f(void) {
	my_modifiers = 0;
  my_modifiers |= (1<<2);  
  my_modifiers |= (1<<3);
	_do_send(KEY_f_F, my_modifiers);	
  return false;
}

//nasty hack... (cough)
uint8_t __key, __modifier;
bool _single_key_handler_hack(void) {
  _do_send(__key, __modifier);
  return true;
}

void _command_handler(bool(*FunctPtr)(void)) {
  //_command_reset();
  bool repeatable = (*FunctPtr)();
  
  if (!repeatable) _repeater = 0;
  
  //WE MAY NEED ANOTHER CHECK FOR NON NORMAL MODE REPEATING>>>...
  if (_repeater <= 1) {
    _repeater = 0;
  } else {
    for (uint8_t i=1; i < _repeater; i++) {
      _do_send(0,0); //it turns out (discovered after much hair pulling) that you need a no-op call in between keypresses
      (*FunctPtr)();
    }
    _repeater = 0;
  }
  _do_command_reset();
}


void _single_key_command(uint8_t key, uint8_t modifier) {
  __key = key;
  __modifier = modifier;
  _command_handler(&_single_key_handler_hack);
}

*/

/*
KEY_LeftControl:(1<<0)
KEY_LeftShift:(1<<1)
KEY_LeftAlt:(1<<2)
KEY_LeftGUI:(1<<3)
KEY_RightControl:(1<<4)
KEY_RightShift:(1<<5)
KEY_RightAlt:  (1<<6)
KEY_RightGUI: (1<<7)
*/

/*

#define _NOTHING _key_pressed = false; return _NORMAL_MODE;
#define _NOTHING_RESET _key_pressed = false; _command_reset = true; return _NORMAL_MODE;

void _repeater_addition(uint8_t adder) {
  _repeater = (_repeater * 10) + adder;
  if (_repeater > 20) { _repeater = 20; } //maybe change later, but this is a safety valve...
}

_STATE __ca(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_w_W:
    
    case _NO_MOD: //daw
    _command_handler(&_do_change_all_word);
    return _INSERT_MODE;    
    break;
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __c(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //da...
      _command_function = &__ca;
      _NOTHING
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_c_C:
    switch (mod) {
      
      case _NO_MOD: //cc
      _command_handler(&_do_change_line);
      return _INSERT_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //cw
      _command_handler(&_do_change_word);
      return _INSERT_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __da(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_w_W:
    
    case _NO_MOD: //daw
    _command_handler(&_do_delete_all_word);
    return _NORMAL_MODE;    
    break;
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __d(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //da...
      _command_function = &__da;
      _NOTHING
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_d_D:
    switch (mod) {
      
      case _NO_MOD: //dd
      _command_handler(&_do_delete_line);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //dw
      _command_handler(&_do_delete_word);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __ya(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_w_W:
    
    case _NO_MOD: //yaw
    _command_handler(&_do_copy_all_word);
    return _NORMAL_MODE;    
    break;
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __y(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //ya...
      _command_function = &__ya;
      _NOTHING
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //yw
      _command_handler(&_do_copy_word);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    
    case KEY_y_Y:
    switch (mod) {
      
      case _NO_MOD: //yy
      _command_handler(&_do_copy_line);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __colon_q(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_ReturnEnter:
    switch (mod) {
      
      case _NO_MOD: //:q(enter)
      _command_handler(&_do_quit);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __colon_w(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_ReturnEnter:
    switch (mod) {
      
      case _NO_MOD: //:w(enter)
      _command_handler(&_do_save);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
    }
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}

_STATE __colon(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_q_Q:
    switch (mod) {
      
      case _NO_MOD: //:q...
      _command_function = &__colon_q;
      _NOTHING
      break;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //:w...
      _command_function = &__colon_w;
      _NOTHING
      break;
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
  
  _NOTHING_RESET
}
  

_STATE _empty_command(uint8_t key, uint8_t mod) {
	
	switch (key) {
        
    case KEY_1_Exclamation:
    switch (mod) {
      case _NO_MOD: //1   
       _repeater_addition(1);
       return _NORMAL_MODE;
       
       break;
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_2_At:
    switch (mod) {
      case _NO_MOD: //2   
       _repeater_addition(2);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_3_Pound:
    switch (mod) {
      case _NO_MOD: //3   
       _repeater_addition(3);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_4_Dollar:
    switch (mod) {
      case _L_SHIFT: //$
      case _R_SHIFT:
      _command_handler(&_do_end_of_line);
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //4   
       _repeater_addition(4);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_5_Percent:
    switch (mod) {
      case _NO_MOD: //5   
       _repeater_addition(5);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_6_Caret:
    switch (mod) {
      case _L_SHIFT: //^
      case _R_SHIFT:
      _command_handler(&_do_soft_beginning_of_line);
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //6   
       _repeater_addition(6);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_7_Ampersand:
    switch (mod) {
      case _NO_MOD: //7   
       _repeater_addition(7);
       return _NORMAL_MODE;
       break;
       
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_8_Asterisk:
    switch (mod) {
      case _NO_MOD: //8   
       _repeater_addition(8);
       return _NORMAL_MODE;
       break;
      
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_9_LeftParenthesis:
    switch (mod) {
      case _NO_MOD: //9
       _repeater_addition(9);
       return _NORMAL_MODE;
       break;
      
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
		case KEY_0_RightParenthesis:
    switch (mod) {
      case _NO_MOD: //0
      //super special case - only means the number 0 when adding onto the repeater 
      //- otherwise it's hard_beginning_of_line...
      if (_repeater > 0) {
        _repeater_addition(0);
      }
      else {
  		  _command_handler(&_do_hard_beginning_of_line);
      }
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
    break;

    case KEY_a_A:
    switch (mod) {
      
      case _L_SHIFT: //A
      case _R_SHIFT:
      _command_handler(&_do_append_eol);
      return _INSERT_MODE;
      break;
      
      case _NO_MOD: //a      
      _command_handler(&_do_append);
      return _INSERT_MODE;
      break;
        
      default:
      _NOTHING_RESET
      break;
    }
    break;

		case KEY_b_B:
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      repeated_key = true;      
      _command_handler(&_do_page_up);      
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //w
      repeated_key = true;      
      _command_handler(&_do_previous_word);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }

    case KEY_c_C:
    switch (mod) {
      
      case _NO_MOD: //c      
      _command_function = &__c;
      _NOTHING
      break;
        
      default:
      _NOTHING_RESET
      break;
    }
    break;
    
    case KEY_d_D:
    switch (mod) {
      
      case _NO_MOD: //d      
      _command_function = &__d;
      _NOTHING
      break;
        
      default:
      _NOTHING_RESET
      break;
    }
    break;

		case KEY_e_E:
    
    switch (mod) {
      case _NO_MOD: //h
      _command_handler(&_do_end_word);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
		break;
    
		case KEY_f_F:
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      repeated_key = true;      
      _command_handler(&_do_page_down);            
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: // f
      _command_handler(&_do_find);
      return _INSERT_MODE_RESET_AND_CR_AFTER_SINGLE_CHAR;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
		case KEY_h_H:
    
    switch (mod) {
      case _NO_MOD: //h
      repeated_key = true;
      _single_key_command(KEY_LeftArrow, 0);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
		break;

		case KEY_i_I:
    
    switch (mod) {
      case _L_SHIFT: //I
      case _R_SHIFT:
      _command_handler(&_do_insert_soft_beginning_of_line);
      return _INSERT_MODE;
      break;
      
      case _NO_MOD: //i
      return _INSERT_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
		break;

		case KEY_j_J:
    
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      repeated_key = true;      
      _command_handler(&_do_scroll_down);      
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //j
      repeated_key = true;
      _single_key_command(KEY_DownArrow, 0);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
		break;

		case KEY_k_K:
    
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      repeated_key = true;      
      _command_handler(&_do_scroll_up);      
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //k
      repeated_key = true;
      _single_key_command(KEY_UpArrow, 0);
      return _NORMAL_MODE;
      break;
      
      default:
      _NOTHING_RESET
      break;
    }
		break;		

		case KEY_l_L:
    switch (mod) {
      case _NO_MOD: //l
      repeated_key = true;
      _single_key_command(KEY_RightArrow, 0);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
		break;

		case KEY_n_N:
    switch (mod) {
      case _L_SHIFT: //N
      case _R_SHIFT:
      _command_handler(&_do_next_find_backward);
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //n
      _command_handler(&_do_next_find_forward);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
		break;  
  
		case KEY_o_O:
    switch (mod) {
      case _L_SHIFT: //I
      case _R_SHIFT:
      _command_handler(&_do_open_line_above);
      return _INSERT_MODE;
      break;
      
      case _NO_MOD: //i
      _command_handler(&_do_open_line_below);
      return _INSERT_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    } 
 
		case KEY_p_P:
    switch (mod) {
      case _L_SHIFT: //P
      case _R_SHIFT:
      _command_handler(&_do_paste_previous_line);
      return _NORMAL_MODE;
      break;
              
      case _NO_MOD: //p
      _command_handler(&_do_paste);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
		break;   

		case KEY_r_R:
    switch (mod) {
      case _NO_MOD: //r
      _command_handler(&_do_select_next_char);
      _exit_function = &_do_back_one_char;
      return _INSERT_MODE_RESET_AFTER_SINGLE_CHAR;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
		case KEY_s_S:
    switch (mod) {
      case _L_SHIFT: //S
      case _R_SHIFT:
      _command_handler(&_do_change_line);
      return _INSERT_MODE;
      break;
      
      case _NO_MOD: //s
      _command_handler(&_subst_char);
      return _INSERT_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }

		case KEY_u_U:
    switch (mod) {
      case _NO_MOD: //u
      _command_handler(&_do_undo);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }


		case KEY_v_V:
    switch (mod) {
      case _L_SHIFT: //S
      case _R_SHIFT:
      return _VISUAL_MODE_LINE;
      break;
      
      case _NO_MOD: //s
      return _VISUAL_MODE_CHAR;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
		case KEY_w_W:
    switch (mod) {
      case _NO_MOD: //w
      repeated_key = true;      
      _command_handler(&_do_next_word);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }

		case KEY_x_X:
    switch (mod) {
      case _L_SHIFT: //X
      case _R_SHIFT:
      repeated_key = true;      
      _single_key_command(KEY_DeleteBackspace, 0);
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //x
      repeated_key = true;      
      _single_key_command(KEY_DeleteForward, 0);
      return _NORMAL_MODE;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
    case KEY_y_Y:
    switch (mod) {
      case _L_COMMAND:
      case _R_COMMAND:
      _command_handler(&_do_copy_selection);
      return _NORMAL_MODE;
      break;
      
      case _NO_MOD: //y   
      _command_function = &__y;
      _NOTHING
      break;
        
      default:
      _NOTHING_RESET
      break;
    }
    break;

		case KEY_Slash_Question:
    switch (mod) {
      
      case _NO_MOD: // /
      _command_handler(&_do_find);
      return _INSERT_MODE_RESET_AFTER_RETURN;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
		case KEY_Semicolon_Colon:
    switch (mod) {
      
      case _L_SHIFT: // :
      case _R_SHIFT:        
      _command_function = &__colon;
      _NOTHING
      break;
    
      default:
      _NOTHING_RESET
      break;
    }
    
  
    
    
		case KEY_F23:
    switch (mod) {
      
      case _NO_MOD: // /
      _command_handler(&_do_command_space);
      return _INSERT_MODE_RESET_AFTER_RETURN;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }    
    
		case KEY_F21:
    switch (mod) {
      
      case _NO_MOD: // /
      _command_handler(&_do_command_option_f);
      return _INSERT_MODE_RESET_AFTER_RETURN;
      break;
    
      default:
      _NOTHING_RESET
      break;
    }       
		
    case KEY_DeleteBackspace:
    case KEY_Spacebar:
    case KEY_DeleteForward:
    case KEY_ReturnEnter:
    case KEY_Tab:
    case KEY_Escape:
    
    _single_key_command(key, mod);
    repeated_key = true;          
    return _NORMAL_MODE;
    break;
  }
  
  _NOTHING_RESET
}

void _do_command_reset(void) {
  _command_function = &_empty_command;
  _command_reset = false;
}

void vim_normal_mode_init(void) {
  _repeater = 0;
  _key_pressed = false;
  _keyboard_state = _NORMAL_MODE;
  //_previous_state = _keyboard_state;  
  _exit_function = 0;
  _do_command_reset();
  visual_mode_line_count = 0;
  visual_mode_entering = true;
  visual_mode_reset = true;
}

_STATE vim_normal_mode_loop(void) {

	//normal_mode = true; //we are currently in normal mode. This may have to change to an int so that we can send 
                      //state back specifically so that we can do 1 character in insert mode - then return to 
                      //normal mode and perhaps there are other edge cases, I haven't mapped them all out.
	
	_key_pressed = false;
  _command_reset = false;
  _keyboard_modifier_keys_temp = keyboard_modifier_keys_temp;


	for (uint8_t i=0; i<6; i++) {
		if (keyboard_keys_temp[i] != 0) {
			repeated_key = false;
      _key_pressed = true;
      
			keyboard_modifier_keys_temp = _keyboard_modifier_keys_temp;
      
			_keyboard_state = (*_command_function)(keyboard_keys_temp[i], keyboard_modifier_keys_temp);
      
      if (!repeated_key) {
        keyboard_keys_temp[i] = 0;    
      }
 
    }

	}
  
  if (_command_reset)
  {
    vim_normal_mode_init();
  }
  
  if (!_key_pressed) {
    //vim_normal_mode_init();
    _do_send(0,0);
  }
	
  	//if (!key_pressed) { //if nothing happened then send over an empty keypress array
  			//usb_keyboard_send();
  	//		_delay_ms(MAKEFILE_DEBOUNCE_TIME);	
  	//}
  
    
	keyboard_modifier_keys_temp = _keyboard_modifier_keys_temp;
	
	return _keyboard_state;
}

*/