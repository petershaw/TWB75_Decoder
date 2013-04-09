//
//  uptime.c
//  AnalyserDude
//
//  Created by Peter Shaw on 4/8/13.
//
//

#include <stdio.h>
#include <util/delay.h>
#include "../../src-lib/lcd/lcd.h"
#include "../control/frontbuttoncontrol.h"
#include "../control/cron.h"

char buf_uptime_string[16];
int lastSec;
lastSec = 60;

void *uptime_update_clock(void){
    lcd_gotoxy(0, 0);
    cron_calculate_hms();
    sprintf(buf_uptime_string, "uptime: %2d:%2d:%2d", cron_hours, cron_minutes, cron_seconds);
    lcd_puts(buf_uptime_string);
}

void *fn_uptime(int init){
    int job;
    if(init == 1){
        // update clock every second
        job = cron_add_job(0, 1, 0, 0, uptime_update_clock);
    }
    frontbuttoncontrol_read();
    while(1){
        if(button_pressed){
            int val = frontbuttoncontrol_get_button();
            if(val == BUTTON_WHITE){
                // stop the job
                
                //leave
            }
        }
       
    }
//    uptime_update_clock();
//    _delay_ms(10);
    
    
}