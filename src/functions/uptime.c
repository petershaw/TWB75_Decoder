//
//  uptime.c
//  AnalyserDude
//
//  Created by Peter Shaw on 4/8/13.
//
//

#include <stdio.h>
#include <util/delay.h>
#include "../global.h"
#include "../../src-lib/lcd/lcd.h"
#include "../control/frontbuttoncontrol.h"
#include "../control/cron.h"

char buf_uptime_string[16];
int lastSec = 0;
//lastSec = 0;

void *uptime_update_clock(void){
    lcd_gotoxy(0, 0);
    cron_calculate_hms();
    sprintf(buf_uptime_string, "uptime: %2d:%2d:%2d", cron_hours, cron_minutes, cron_seconds);
    return((void *)0);
}

void *fn_uptime(int init){
    int job = 0;
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
                if(job > 0){
                    cron_remove_job(job);
                }
                //leave
                break;
            }
        }
        if(lastSec != cron_seconds){
            lcd_puts(buf_uptime_string);
            lastSec = cron_seconds;
        }
    }
    stopApplication();
    return((void *)0);
}