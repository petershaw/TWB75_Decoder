
#ifndef twb75_II_h
#define twb75_II_h

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define ifStateChangeOn(a, b) 		if((a == false) && (b == true))
#define ifStateChangeOff(a, b) 	if((a == true) && (b == false))

#define showDebugMsg(a)			if(opt_send_data_via_uart){ \
									if(a == 1){ uart_puts( "ON: (" ); } \
									else { uart_puts( "OFF: (" ); }\
									itoa( impulse_time, twb_debug_buffer, 10); \
									uart_puts( twb_debug_buffer ); \
									uart_puts( " ms)\n" ); \
								}

uint8_t twb_current_value;
uint8_t twb_current_position;
char    twb_buffer[16];

volatile bool    twb_is_session_active;
volatile bool    twb_is_sequence_active;
volatile bool    twb_is_impulse_active;

volatile uint32_t impulse_time;

bool 	twb_last_state;
bool 	twb_current_state;

int 	twb_timeout_session;

void *fn_twb75_II(int init);

#endif
