#ifndef LIB_VIMYAK_KEY_FUNCTIONS_h
	#define LIB_VIMYAK_KEY_FUNCTIONS_h

	#include <stdbool.h>
	#include <stdint.h>

#define _STATE                                               uint8_t
#define   _NORMAL_MODE                                          0
#define   _INSERT_MODE                                          1
#define   _INSERT_MODE_RESET_AFTER_SINGLE_CHAR                  2
#define   _INSERT_MODE_RESET_AFTER_RETURN                       3
#define   _INSERT_MODE_RESET_AND_CR_AFTER_SINGLE_CHAR           4
#define   _VISUAL_MODE_CHAR                                     5
#define   _VISUAL_MODE_LINE                                     6
  
  
#define _NO_MOD           0
#define _L_CONTROL        1
#define _L_SHIFT          2
#define _L_OPTION         4
#define _L_COMMAND        8
#define _R_CONTROL        16
#define _R_SHIFT          32
#define _R_OPTION         64
#define _R_COMMAND        128

void vimyak_init(void);
void vimyak_keyhandler(void);

void set_clear_buffer(void);
void set_skip_further_commands(void);
void set_repeatable_key(void);
void set_repeatable_modified_key(void);

_STATE get_keyboard_state(void);
void set_keyboard_state(_STATE new_state);
  
#endif