#include <util/delay.h>
#include "./normal-mode.h"
#include "./mode-utilities.h"
#include "../vimyak.h"

//keycodes for switch
#include "../../lib/usb/usage-page/keyboard.h"

//repeater #defines/vars
uint8_t repeater_index;
#define _SR_ repeater_index=1; while(repeater_index<repeater) {__do_send(0,0);  //start repeater loop
#define _ER_ repeater_index++; } //end repeater loop

uint8_t my_modifiers;

//a
void _do_append(uint8_t repeater) {
  my_modifiers = 0;
	__do_send(KEY_RightArrow, my_modifiers);
}

//A
void _do_append_eol(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |=  (1<<3);
	
	__do_send(KEY_RightArrow, my_modifiers);
  
  
}

//b
void _do_previous_word(uint8_t repeater) {
  __do_left_word(false);
}

//^b
void _do_page_down(uint8_t repeater) {
  __go_page_down();
}
  

//cc
void _do_change_line(uint8_t repeater) {
  
  __go_beginning_of_line(false);
  
  _SR_
  __do_down(true); 
  _ER_
    
  __go_end_of_line(true);
  __do_copy_selection();
  
  __do_delete_backwards();   
  
}

//caw 
void _do_change_all_word(uint8_t repeater) {
  __do_select_all_word();
  __do_copy_selection();
  __do_delete_backwards();
}

//cw
void _do_change_word(uint8_t repeater) {
  __do_right_word(true);
  _SR_
  __do_right_word(true);
  _ER_
    
  __do_delete_backwards(); 
}

//daw
void _do_delete_all_word(uint8_t repeater) {
  __do_select_all_word();
  
  my_modifiers = 0;
  __do_send(KEY_DeleteBackspace, my_modifiers);
  
}

//dd
void _do_delete_line(uint8_t repeater) {
  __do_set_mark();
  __go_beginning_of_line(false);
  
  _SR_
  __do_down(true); 
  _ER_
    
  __go_end_of_line(true);
  __do_copy_selection();
  __do_swap_with_mark();
  
  __do_insert_space();
  __go_beginning_of_line(false);
  
  _SR_
  __do_down(true); 
  _ER_
    
  __go_end_of_line(true);
  __do_delete_backwards(); 
  __do_send(0,0); 
  __do_delete_backwards();   
}

//dw
void _do_delete_word(uint8_t repeater) {
  __do_right_word(true);  
  _SR_
  __do_right_word(true);
  _ER_
  __do_copy_selection();
  __do_delete_backwards();
  
}

//d$
void _do_delete_to_end_of_line(uint8_t repeater) {
  __go_end_of_line(true);
  __do_copy_selection();
  __do_delete_backwards();
}

//e
void _do_end_word(uint8_t repeater) {
  __do_select_all_word();
  
  my_modifiers = 0;
  __do_send(KEY_RightArrow, my_modifiers);
  
}

//one two three four five

//^f
void _do_page_up(uint8_t repeater) {
  __go_page_up();
}

//exit function for f
void _escape_and_find_char_forward(void) {
	my_modifiers = 0;
  __do_send(KEY_Escape, my_modifiers);
  __do_send(0,0);
  __do_find_forward();  
}
//exit function for F
void _escape_and_find_char_backward(void) {
	my_modifiers = 0;
  __do_send(KEY_Escape, my_modifiers);
  __do_send(0,0);
  __do_find_backward();  
}


//G
void _do_end_of_file(uint8_t repeater) {
  __do_select_all_file();
  __do_right(false);
}

//gg
void _do_beginning_of_file(uint8_t repeater) {
  __do_select_all_file();
  __do_left(false);
}

//I
void _do_insert_soft_beginning_of_line(uint8_t repeater) {
  __go_soft_beginning_of_line();
  
}

//^j
void _do_scroll_up(uint8_t repeater) {
  __do_scroll_up();
  
}

//^k
void _do_scroll_down(uint8_t repeater) {
  __do_scroll_down();  
  
}

//n
void _do_next_find_forward(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	__do_send(KEY_g_G, my_modifiers);
  
}

//N
void _do_next_find_backward(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	my_modifiers |= (1<<1);
	__do_send(KEY_g_G, my_modifiers);
  
}


//o
void _do_open_line_below(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	__do_send(KEY_RightArrow, my_modifiers);
	
  my_modifiers = 0;
  __do_send(KEY_ReturnEnter, my_modifiers);
  
}


//O
void _do_open_line_above(uint8_t repeater) {
	__go_soft_beginning_of_line();
	
  my_modifiers = 0;
  __do_send(KEY_ReturnEnter, my_modifiers);
  
  my_modifiers = 0;
  __do_send(KEY_UpArrow, my_modifiers);
  
}

//p
void _do_paste(uint8_t repeater) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_RightArrow, my_modifiers);
  my_modifiers = 0;
  __do_send(KEY_ReturnEnter, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_LeftArrow, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_v_V, my_modifiers);
  
}

//P
void _do_paste_previous_line(uint8_t repeater) {
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_LeftArrow, my_modifiers);
  my_modifiers = 0;
  __do_send(KEY_ReturnEnter, my_modifiers);
  my_modifiers = 0;
  __do_send(KEY_UpArrow, my_modifiers);
  my_modifiers = 0;
  my_modifiers |= (1<<3);
  __do_send(KEY_v_V, my_modifiers);
  
}

//r
void _do_select_next_char(uint8_t repeater) {
  my_modifiers = 0;
  my_modifiers |= (1<<1);
  __do_send(KEY_RightArrow, my_modifiers);
  
}

//r - exit function
void _do_back_one_char(void) {
  my_modifiers = 0;
  __do_send(KEY_LeftArrow, my_modifiers);
  
}

//s
void _subst_char(uint8_t repeater) {
	my_modifiers = 0;
	__do_send(KEY_DeleteForward, my_modifiers);
  
}

//S
//see change_line()


//u
void _do_undo(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |=  (1<<3);
	
	__do_send(KEY_z_Z, my_modifiers);
  
}

//V
void _do_visual_mode_line_exit_function(uint8_t repeater) {
  __do_swap_with_mark();
  
}

//w
void _do_next_word(uint8_t repeater) {
  __do_right_word(false);
}

//yy
void _do_copy_line(uint8_t repeater) {
  __do_set_mark();  
  __go_beginning_of_line(false);
  
  _SR_
  __do_down(true); 
  _ER_
    
  __go_end_of_line(true);
  __do_copy_selection();  
  __do_swap_with_mark();
}

//yaw 
void _do_copy_all_word(uint8_t repeater) {
  __do_set_mark();
  __do_select_all_word();
  __do_copy_selection();
  __do_swap_with_mark();
  
  
}

//yw
void _do_copy_word(uint8_t repeater) {
  __do_right_word(true);
  _SR_
  __do_right_word(true);  
  _ER_
    
  __do_copy_selection();
  __do_left(false);
  
}


//ys - my personal copy selection for mouse selected text primarily
void _do_copy_selection(uint8_t repeater) {
  __do_copy_selection();  
}

// / + ?
void _do_find(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
	__do_send(KEY_f_F, my_modifiers);
  
}

//escape function for: ?
void _do_escape_and_find_backward(void) {
	my_modifiers = 0;
  __do_send(KEY_Escape, my_modifiers);
  __do_send(0,0);
  __do_find_backward();
}

//escape function for: /
void _do_escape_and_find_forward(void) {
	my_modifiers = 0;
  __do_send(KEY_Escape, my_modifiers);
  __do_send(0,0);
  __do_find_forward();
}

//0
void _do_hard_beginning_of_line(uint8_t repeater) {
	my_modifiers = 0;
	my_modifiers |= (1<<3);
  __do_send(KEY_LeftArrow, my_modifiers);
  
}

//^
void _do_soft_beginning_of_line(uint8_t repeater) {
  __go_soft_beginning_of_line();
  
  
}

//$
void _do_end_of_line(uint8_t repeater) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	__do_send(KEY_RightArrow, my_modifiers);	
  
}

//:q(enter)
void _do_quit(uint8_t repeater) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	__do_send(KEY_q_Q, my_modifiers);	
  
}

//:x(enter)
void _do_save(uint8_t repeater) {
	my_modifiers = 0;
  my_modifiers |= (1<<3);
	__do_send(KEY_s_S, my_modifiers);	
  
}

//f23 + f21 -see shared recipes

//nasty hack... (cough)
uint8_t __key, __modifier;
void _single_key_handler_hack(uint8_t repeater) {
  __do_send(__key, __modifier);  
  _SR_
  __do_send(__key, __modifier);
  _ER_
}

void _command_handler(void(*FunctPtr)(uint8_t)) {

  (*FunctPtr)(_get_repeater());
  _reset_repeater();
  _do_command_reset();
}


void _single_key_command(uint8_t key, uint8_t modifier) {
  __key = key;
  __modifier = modifier;
  _command_handler(&_single_key_handler_hack);
}

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


void __ca(uint8_t key, uint8_t mod) {
  switch (key) {
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //caw
      _command_handler(&_do_change_all_word);
      _set_state(_INSERT_MODE);    
      _NOTHING
        
      default:
      _NOTHING_RESET
    } 
      
    default:
    _NOTHING_RESET
  }
}

void __c(uint8_t key, uint8_t mod) {
  switch (key) {
    
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //da...
      _set_command_function(&__ca);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_c_C:
    switch (mod) {
      
      case _NO_MOD: //cc
      _command_handler(&_do_change_line);
      _set_state(_INSERT_MODE);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //cw
      _command_handler(&_do_change_word);
      _set_state(_INSERT_MODE);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
}

void __da(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_w_W:
    
    case _NO_MOD: //daw
    _command_handler(&_do_delete_all_word);
    _NOTHING; 
    
    default:
    _NOTHING_RESET
  }
}

void __d(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //da...
      _set_command_function(&__da);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_d_D:
    switch (mod) {
      
      case _NO_MOD: //dd
      _command_handler(&_do_delete_line);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //dw
      _command_handler(&_do_delete_word);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_4_Dollar:
    switch (mod) {
      
      case _L_SHIFT: //dw
      case _R_SHIFT:
      _command_handler(&_do_delete_to_end_of_line);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    } 
    
    default:
    _NOTHING_RESET
  }
}



void __g(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_g_G:
    
    case _NO_MOD: //gg
    _command_handler(&_do_beginning_of_file);
    _NOTHING;  
    
    default:
    _NOTHING_RESET
  }
}


void __ya(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_w_W:
    
    case _NO_MOD: //yaw
    _command_handler(&_do_copy_all_word);
    _NOTHING; 
    
    default:
    _NOTHING_RESET
  }
}

void __y(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_a_A:
    switch (mod) {
      
      case _NO_MOD: //ya...
      _set_command_function(&__ya);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //yw
      _command_handler(&_do_copy_word);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_s_S:
    switch (mod) {
      
      case _NO_MOD: //ys - Themios's personal copy for mouse selected text
      _command_handler(&_do_copy_selection);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    
    case KEY_y_Y:
    switch (mod) {
      
      case _NO_MOD: //yy
      _command_handler(&_do_copy_line);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
}

void __colon_q(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_ReturnEnter:
    switch (mod) {
      
      case _NO_MOD: //:q(enter)
      _command_handler(&_do_quit);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    default:
    _NOTHING_RESET
  }
}

void __colon_w(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_ReturnEnter:
    switch (mod) {
      
      case _NO_MOD: //:w(enter)
      _command_handler(&_do_save);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    
    default:
    _NOTHING_RESET
  }
}

void __colon(uint8_t key, uint8_t mod) {
  switch (key) {
    case KEY_q_Q:
    switch (mod) {
      
      case _NO_MOD: //:q...
      _set_command_function(&__colon_q);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    case KEY_w_W:
    switch (mod) {
      
      case _NO_MOD: //:w...
      _set_command_function(&__colon_w);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    
    
    default:
    _NOTHING_RESET
  }
}
  
void _empty_command(uint8_t key, uint8_t mod) {
	
	switch (key) {
        
    case KEY_1_Exclamation:
    switch (mod) {
      case _NO_MOD: //1   
       _repeater_addition(1);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_2_At:
    switch (mod) {
      case _NO_MOD: //2   
       _repeater_addition(2);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_3_Pound:
    switch (mod) {
      case _NO_MOD: //3   
       _repeater_addition(3);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_4_Dollar:
    switch (mod) {
      case _L_SHIFT: //$
      case _R_SHIFT:
      _command_handler(&_do_end_of_line);
      _NOTHING;
      
      case _NO_MOD: //4   
       _repeater_addition(4);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_5_Percent:
    switch (mod) {
      case _NO_MOD: //5   
       _repeater_addition(5);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_6_Caret:
    switch (mod) {
      case _L_SHIFT: //^
      case _R_SHIFT:
      _command_handler(&_do_soft_beginning_of_line);
      _NOTHING;
      
      case _NO_MOD: //6   
       _repeater_addition(6);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_7_Ampersand:
    switch (mod) {
      case _NO_MOD: //7   
       _repeater_addition(7);
       _NOTHING;
       
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_8_Asterisk:
    switch (mod) {
      case _NO_MOD: //8   
       _repeater_addition(8);
       _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_9_LeftParenthesis:
    switch (mod) {
      case _NO_MOD: //9
       _repeater_addition(9);
       _NOTHING;
      
      default:
      _NOTHING_RESET
    }
    break;
    
		case KEY_0_RightParenthesis:
    switch (mod) {
      case _NO_MOD: //0
      //super special case - only means the number 0 when adding onto the repeater 
      //- otherwise it's hard_beginning_of_line...
      if (_get_repeater() > 0) {
        _repeater_addition(0);
      }
      else {
  		  _command_handler(&_do_hard_beginning_of_line);
      }
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
    break;

    case KEY_a_A:
    switch (mod) {
      
      case _L_SHIFT: //A
      case _R_SHIFT:
      _command_handler(&_do_append_eol);
      _set_state(_INSERT_MODE);
      _NOTHING
      
      case _NO_MOD: //a      
      _command_handler(&_do_append);
      _set_state(_INSERT_MODE);
      _NOTHING
        
      default:
      _NOTHING_RESET
    }
    break;

		case KEY_b_B:
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      set_repeatable_modified_key();      
      _command_handler(&_do_page_up);      
      _NOTHING
      
      case _NO_MOD: //b
      set_repeatable_modified_key();      
      _command_handler(&_do_previous_word);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }

    case KEY_c_C:
    switch (mod) {      
      case _NO_MOD: //c      
      _set_command_function(&__c);
      _NOTHING
        
      default:
      _NOTHING_RESET
    }
    break;
    
    case KEY_d_D:
    switch (mod) {      
      case _NO_MOD: //d      
      _set_command_function(&__d);
      _NOTHING
        
      default:
      _NOTHING_RESET
    }
    break;

		case KEY_e_E:    
    switch (mod) {
      case _NO_MOD: //h
      _command_handler(&_do_end_word);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
		break;
    
		case KEY_f_F:
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      set_repeatable_modified_key();      
      _command_handler(&_do_page_down);            
      _NOTHING;
      
      case _L_SHIFT: //F
      case _R_SHIFT:
      _command_handler(&_do_find);
      _set_state(_INSERT_MODE_RESET_AFTER_SINGLE_CHAR);      
      _exit_function = &_escape_and_find_char_backward;
      _NOTHING
      
      case _NO_MOD: // f
      _command_handler(&_do_find);
      _set_state(_INSERT_MODE_RESET_AFTER_SINGLE_CHAR);      
      _exit_function = &_escape_and_find_char_forward;
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
		case KEY_g_G:    
    switch (mod) {
      case _L_SHIFT: //G
      case _R_SHIFT:
      _command_handler(&_do_end_of_file);
      _NOTHING
      
      case _NO_MOD: //g     
      _set_command_function(&__g);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
		break;
        
		case KEY_h_H:    
    switch (mod) {
      case _NO_MOD: //h
      set_repeatable_modified_key();
      _single_key_command(KEY_LeftArrow, 0);
      _NOTHING;
      
      default:
      _NOTHING_RESET
    }
		break;

		case KEY_i_I:    
    switch (mod) {
      case _L_SHIFT: //I
      case _R_SHIFT:
      _command_handler(&_do_insert_soft_beginning_of_line);
      _set_state(_INSERT_MODE);
      _NOTHING
      
      case _NO_MOD: //i
      _set_state(_INSERT_MODE);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
		break;

		case KEY_j_J:    
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      set_repeatable_modified_key();     
      _command_handler(&_do_scroll_down);      
      _NOTHING
      
      case _NO_MOD: //j
      set_repeatable_modified_key();
      _single_key_command(KEY_DownArrow, 0);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
		break;

		case KEY_k_K:    
    switch (mod) {
      case _L_CONTROL:
      case _R_CONTROL:
      set_repeatable_modified_key(); 
      _command_handler(&_do_scroll_up);      
      _NOTHING
      
      case _NO_MOD: //k
      set_repeatable_modified_key();
      _single_key_command(KEY_UpArrow, 0);
      _NOTHING
      
      default:
      _NOTHING_RESET
    }
		break;		

		case KEY_l_L:
    switch (mod) {
      case _NO_MOD: //l
      set_repeatable_modified_key();
      _single_key_command(KEY_RightArrow, 0);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
		break;

		case KEY_n_N:
    switch (mod) {
      case _L_SHIFT: //N
      case _R_SHIFT:
      _command_handler(&_do_next_find_backward);
      _NOTHING
      
      case _NO_MOD: //n
      _command_handler(&_do_next_find_forward);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
		break;  
  
		case KEY_o_O:
    switch (mod) {
      case _L_SHIFT: //I
      case _R_SHIFT:
      _command_handler(&_do_open_line_above);
      _set_state(_INSERT_MODE);
      _NOTHING
      
      case _NO_MOD: //i
      _command_handler(&_do_open_line_below);
      _set_state(_INSERT_MODE);
      _NOTHING
    
      default:
      _NOTHING_RESET
    } 
 
		case KEY_p_P:
    switch (mod) {
      case _L_CONTROL: //^p
      case _R_CONTROL:
      __do_paste();         
      _NOTHING  
      
      case _L_SHIFT: //P
      case _R_SHIFT:
      _command_handler(&_do_paste_previous_line);
      _NOTHING
              
      case _NO_MOD: //p
      _command_handler(&_do_paste);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
		break;   

		case KEY_r_R:
    switch (mod) {
      case _NO_MOD: //r
      _command_handler(&_do_select_next_char);
      _set_state(_INSERT_MODE_RESET_AFTER_SINGLE_CHAR);
      _exit_function = &_do_back_one_char;      
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
		case KEY_s_S:
    switch (mod) {
      case _L_SHIFT: //S
      case _R_SHIFT:
      _command_handler(&_do_change_line);
      _set_state(_INSERT_MODE);
      _NOTHING      
      
      case _NO_MOD: //s
      _command_handler(&_subst_char);
      _set_state(_INSERT_MODE);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }

		case KEY_u_U:
    switch (mod) {
      case _NO_MOD: //u
      _command_handler(&_do_undo);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }


		case KEY_v_V:
    switch (mod) {
      case _L_SHIFT: //S
      case _R_SHIFT:
      _set_state(_VISUAL_MODE_LINE);
      _NOTHING
      
      case _NO_MOD: //s
      _set_state(_VISUAL_MODE_CHAR);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
		case KEY_w_W:
    switch (mod) {
      case _NO_MOD: //w
      set_repeatable_modified_key();    
      _command_handler(&_do_next_word);
      _NOTHING
          
      default:
      _NOTHING_RESET
    }

		case KEY_x_X:
    switch (mod) {
      case _L_SHIFT: //X
      case _R_SHIFT:
      set_repeatable_modified_key();
      _single_key_command(KEY_DeleteBackspace, 0);
      _NOTHING
      
      case _NO_MOD: //x
      set_repeatable_modified_key();      
      _single_key_command(KEY_DeleteForward, 0);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
    case KEY_y_Y:
    switch (mod) {
      
      case _NO_MOD: //y   
      _set_command_function(&__y);
      _NOTHING
        
      default:
      _NOTHING_RESET
    }
    break;

		case KEY_Slash_Question:
    switch (mod) {
      case _L_SHIFT: //?
      case _R_SHIFT:
      _command_handler(&_do_find);
      _set_state(_INSERT_MODE_RESET_BUT_DISREGARD_CR);
      _exit_function = &_do_escape_and_find_backward;                  
      _NOTHING
      
      
      case _NO_MOD: // /
      _command_handler(&_do_find);
      _set_state(_INSERT_MODE_RESET_BUT_DISREGARD_CR);
      _exit_function = &_do_escape_and_find_forward;            
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
		case KEY_Semicolon_Colon:
    switch (mod) {
      
      case _L_SHIFT: // :
      case _R_SHIFT:        
      _set_command_function(&__colon);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
    
		case KEY_Backslash_Pipe:
    switch (mod) {
      
      case _L_COMMAND: // /
      case _R_COMMAND:      
      set_repeatable_key();
      _set_state(_INSERT_MODE_RESET_AFTER_RETURN);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
    
    
		case KEY_F23:
    switch (mod) {
      
      case _NO_MOD: // /
      _command_handler(&_do_command_space);
      _set_state(_INSERT_MODE_RESET_AFTER_RETURN);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }    
    
		case KEY_F21:
    switch (mod) {
      
      case _NO_MOD: // /
      _command_handler(&_do_command_option_alt_f);
      _set_state(_INSERT_MODE_RESET_AFTER_RETURN);
      _NOTHING
    
      default:
      _NOTHING_RESET
    }
		
    case KEY_DeleteBackspace:
    case KEY_Spacebar:
    case KEY_DeleteForward:
    case KEY_ReturnEnter:
    case KEY_Tab:
    case KEY_Escape:
    
    set_repeatable_key();
    _NOTHING
    
    default:
    _NOTHING_RESET
  }
}


void normal_mode_loop(uint8_t key, uint8_t mod) {
  (*_command_function)(key, mod);
}

void normal_mode_setup(void) {
  _command_function = &_empty_command;
}