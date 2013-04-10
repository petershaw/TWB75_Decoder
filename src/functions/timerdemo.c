//
//  timerdemo.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/31/13.
//
//
//  Show the timer functionality of the cron facility
//  The green butten can pressed  multible times to decode the
//  value the character should get.
//  To jump to the next character the time betwween two presses
//  the gab between them must be
//  greater than 10 secounds.
//


#include <stdio.h>
#include "../global.h"

#include "../../src-lib/lcd/lcd.h"

#include "../control/frontbuttoncontrol.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"
#include "../control/cron.h"

#include "timerdemo.h"

void _timerDemo_increment_current_value(void){
    ++timerDemo_current_value;
}

void _timerDemo_update_lcd(void){
    // build string
    if(timerDemo_current_value > (ASCII_BEGIN_NUMBERS +9) -1){
        timerDemo_current_value = 0;
    }
    timerDemoBuffer[timerDemo_current_charackter_position] = (ASCII_BEGIN_NUMBERS -1) + timerDemo_current_value;

    // display
    lcd_clrscr();
    lcd_puts(timerDemoBuffer);
}

void *_timerDemo_step_characketer_position(void){
    ++timerDemo_current_charackter_position;
    if(timerDemo_current_charackter_position <= 7){
        timerDemo_current_charackter_position = 0;
    }
    return((void *)0);
}

void *fn_timerDemo(int init){
    if(init == 1) {
        timerDemo_current_value = 0;
        timerDemo_current_charackter_position = 0;
        timerDemo_last_button_pressed = 0;
        sprintf(timerDemoBuffer, "________");
    }

    frontbuttoncontrol_read();
    if(button_pressed){
        int val = frontbuttoncontrol_get_button();
        if(val == BUTTON_GREEN && timerDemo_last_button_pressed != BUTTON_GREEN){
            timerDemo_last_button_pressed = BUTTON_GREEN;
            _timerDemo_increment_current_value();
            cron_set_timeout(timerDemo_TIMEOUT_ID, 0, 10, 0, 0, _timerDemo_step_characketer_position);
            _timerDemo_update_lcd();
        }
    } else {
        timerDemo_last_button_pressed = 0;
    }
    
    return((void *)0);
}