//
// Read out the TWB75
//

#include <stdlib.h>
#include "../../src-lib/lcd/lcd.h"
#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"
#include "../control/cron.h"
#include "../control/frontbuttoncontrol.h"
#include "../../src-lib/uart/uart.h"

#include "twb75_II.h"

char    twb_debug_buffer[10];
uint32_t impulse_change_time_start;
uint32_t impulse_start_time;
uint32_t impulse_ends_time;


/**
 * Print the whole buffer to the lcd
 */
void _twb75_update_lcd(void){
    // build string
    lcd_gotoxy(0, 1);
    lcd_puts(twb_buffer);
}

/**
 * Step a character position forward
 */
void _twb75_step_characketer_position(void){
    LIGHT_ON(LED_RED);
    char buf[1];
    itoa(twb_current_value, buf, 10);
    twb_buffer[twb_current_position] = buf[0];
    lcd_gotoxy(14, 0);
    lcd_puts(buf);
    ++twb_current_position;
    twb_current_value = 0;
    if(twb_current_position >= 16){
        twb_current_position = 0;
        sprintf(twb_buffer, "               ");
    }
    twb_buffer[twb_current_position] = "";
    _twb75_update_lcd();
    LIGHT_OFF(LED_RED);
}

/** 
	if the last impulse is > 100, or the session should ends, 
	than stop the sequence!
*/
void twb75_stop_sequence(void){
	twb_is_sequence_active = false;
	twb_is_impulse_active = false;
	if(twb_current_value == 10) twb_current_value = 0;
	_twb75_step_characketer_position();
	debug( "seq stops\n" );
	itoa(twb_current_value, twb_debug_buffer, 10);
	debug(twb_current_value);
	twb_current_value = 0;
}

/**
 * Callback if a session ends
 */
void twb75_stop_session(void){	    
    twb75_stop_sequence();
    
    twb_is_session_active = false;
    twb_is_impulse_active = false;
    
    impulse_ends_time = NULL;
        
    debug( "session stops\n\n" );
}

/**
 * State Maschine When Amplitude gets Heigh
 */
 void _onAmplitudeHigh(void){
 	showDebugMsg(1);
 }

/**
 * State Maschine When Amplitude gets Low
 */
 void _onAmplitudeLow(void){
 	showDebugMsg(0);
 	// handle control comands
 	if(impulse_time > 650){
 		if(twb_is_session_active == false){
			twb_is_session_active = true;
			twb_is_sequence_active = true;
			debug( "session starts" );
			debug( "seq starts" );
			cron_set_timeout(twb_timeout_session, 100, 1, 0, 0, &twb75_stop_session);
		} else {
			if(twb_is_sequence_active == true){
				// this must be the end of a sequence - next sequence
				++twb_current_value;
				twb75_stop_sequence();
				twb_is_sequence_active = true;
				
				debug("new sequence");
				
			}
			// renew session
			cron_set_timeout(twb_timeout_session, 100, 1, 0, 0, &twb75_stop_session);
		}
 	} else if(impulse_time > 20){
 		debug( "Impulse!\n" );
 		++twb_current_value;
 		// renew session
		cron_set_timeout(twb_timeout_session, 100, 1, 0, 0, &twb75_stop_session);
 	}
 }
 
 
/**
 * Reads out the digital blue port of the AnalyserDude and process the state mashine
 */
void _twb75_BluePort_read(void){
	/** 
	 * The blue port is bound to the optocopler network. It's connected to the PISO 
	 * shift reqister.
	 */
	// Read ot the shift register
    PISO_INHIBIT_PORT |= PISO_INHIBIT_PIN;                  // Disable clock listener
    
    PISO_CLOCK_PORT |= PISO_CLOCK_PIN;                      // turn clock high
    PISO_LOAD_PORT  &= ~PISO_LOAD_PIN;                      // LOW on LOAD -> load the register
    PISO_LOAD_PORT  |= PISO_LOAD_PIN;                       // HIGH on LOAD
    
    PISO_CLOCK_PORT &= ~PISO_CLOCK_PIN;                     // turn clock low
    PISO_INHIBIT_PORT &= ~PISO_INHIBIT_PIN;
    
    int i;
    int a;   
    int r = 0;                                                                                           // result button number
    for(i=0; i<4; ++i){
        a = 0;
        if(PISO_OUTPUT_PORT & (1<<PISO_OUTPUT_PIN_NAME)){   // welcher wert steht in PINB & (1<<PB4)?
            a = a >> 2 ^(i+1);                              // Pressed!
        }
        
        r = r + (a);
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;                  // toggle clock -- shift the register
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;
    }

    if(r == BUTTON_BLUE){
    	twb_current_state = true;
    } else {
    	twb_current_state = false;
    }
    
    // on off toggle
    ifStateChangeOn(twb_last_state, twb_current_state){
    	impulse_start_time = system_millisecunds_since_startup;
    	if(impulse_ends_time){
    		impulse_time = system_millisecunds_since_startup - impulse_ends_time;
    	} else {
    		impulse_time = -1;
    	}
    	_onAmplitudeHigh();
    } else ifStateChangeOff(twb_last_state, twb_current_state){
    	impulse_ends_time = system_millisecunds_since_startup;
    	impulse_time = system_millisecunds_since_startup - impulse_start_time;
    	_onAmplitudeLow();
    }
    
	twb_last_state = twb_current_state;
}

/**
 * Run method. 
 * This method will call every AnalyserDude-Loop.
 */
void *fn_twb75_II(int init){
    
    on_init {
        debug( "Init twb75 readout" );

        twb_last_state          = false;
		twb_current_state       = false;

        twb_is_session_active 	= false;
        twb_is_sequence_active 	= false;
        twb_is_impulse_active 	= false;

        twb_current_value 		= 0;
        twb_current_position 	= 0;
        
        twb_timeout_session 	= 1;
        
        sprintf(twb_buffer, 	"________________");
        lcd_gotoxy(0, 0);
        lcd_puts("TWB75 Numbers:");
        
        _twb75_update_lcd();
    }
	
    _twb75_BluePort_read();
    return((void *)0);
}