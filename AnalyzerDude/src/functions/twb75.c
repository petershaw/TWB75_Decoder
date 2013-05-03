//
// Read out the TWB75
//

#include "../../src-lib/lcd/lcd.h"

#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"
#include "../control/cron.h"

#include "twb75.h"

void _twb75_update_lcd(void){
    // build string
    
    lcd_gotoxy(0, 1);
    lcd_puts(twb_buffer);
}

void _twb75_step_characketer_position(void){
    LIGHT_ON(LED_RED);
    
    char buf[1];
    itoa(twb_current_value, buf, 10);
    twb_buffer[twb_current_charackter_position] = buf[0];
    lcd_gotoxy(14, 0);
    lcd_puts(buf);
    
    ++twb_current_charackter_position;
    twb_current_value = 0;
    if(twb_current_charackter_position >= 16){
        twb_current_charackter_position = 0;
        sprintf(twb_buffer, "               ");
    }
    twb_buffer[twb_current_charackter_position] = "";
    _twb75_update_lcd();
    LIGHT_OFF(LED_RED);
}

void _twb75_start_sequence_listener(void){
     twb_is_sequ_active = true;
}
void _twb75_stop_sequence_listener(void){
    twb_is_sequ_active = false;
}

void _twb75_BluePort_read(void){
    PISO_INHIBIT_PORT |= PISO_INHIBIT_PIN;                  // Disable clock listener
    
    PISO_CLOCK_PORT |= PISO_CLOCK_PIN;                      // turn clock high
    PISO_LOAD_PORT  &= ~PISO_LOAD_PIN;                      // LOW on LOAD -> load the register
    PISO_LOAD_PORT  |= PISO_LOAD_PIN;                       // HIGH on LOAD
    
    PISO_CLOCK_PORT &= ~PISO_CLOCK_PIN;                     // turn clock low
    PISO_INHIBIT_PORT &= ~PISO_INHIBIT_PIN;
    
    int i;
    int a;                                                  // current value
    int r = 0;                                              // result button number
    for(i=0; i<4; i++){
        a = 0;
        if(PISO_OUTPUT_PORT & (1<<PISO_OUTPUT_PIN_NAME)){   // welcher wert steht in PINB & (1<<PB4)?
            a = a >> 2 ^(i+1);                              // Pressed!
        }
        r = r + (a);
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;                  // toggle clock -- shift the register
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;
    }
    
    // Debounce
    if(r == 1 && !twb_is_port_active){
        LIGHT_ON(LED_RED);
        if(twb_is_sequ_active == false){
            cron_set_timeout(twb_startseq, 20, 0, 0, 0, _twb75_start_sequence_listener);
            cron_remove_timeout(twb_stopseq);
            return;
        }
        cron_set_timeout(twb_finischseq, 110, 0, 0, 0, _twb75_step_characketer_position);
        twb_is_port_active = true;
        ++twb_current_value;
    }
    if(r != 1 && twb_is_port_active){
        twb_is_port_active = false;
        cron_set_timeout(twb_stopseq, 300, 0, 0, 0, _twb75_stop_sequence_listener);
        LIGHT_OFF(LED_RED);
    }
}

void *fn_twb75(int init){
    
    on_init {
        twb_is_port_active = false;
        twb_is_sequ_active = false;
        twb_finischseq  = 1;
        twb_startseq    = 2;
        twb_stopseq     = 3;
        twb_current_value = 0;
        twb_current_charackter_position = 0;
        sprintf(twb_buffer, "________________");
        lcd_gotoxy(0, 0);
        lcd_puts("TWB75 Numbers:");
        _twb75_update_lcd();
    }

    _twb75_BluePort_read();
    return((void *)0);
}