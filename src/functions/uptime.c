//
//  uptime.c
//  AnalyserDude
//
//  Created by Peter Shaw on 4/8/13.
//
//
//  Show the time in hh:mm:ss the system is running.
//  This fnction uses the cron facility to update the string buffer.
//

#include <stdio.h>
#include <util/delay.h>
#include "../global.h"
#include "../../src-lib/lcd/lcd.h"
#include "../control/frontbuttoncontrol.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"
#include "../control/cron.h"

char buf_uptime_string[16];
char buf_systemtime_string[16];
int lastSec = 60;   // never reached, so the first tick will change the value and updtes the display
int _uptime_job = 0;

void *uptime_update_clock(void){
    LIGHT_TOGGLE(LED_RED);
    cron_calculate_uptime_hms();
    sprintf(buf_uptime_string, "uptime: %02d:%02d:%02d", cron_hours, cron_minutes, cron_seconds);
    sprintf(buf_systemtime_string, "%ld ms up\n", system_millisecunds_since_startup);

    return((void *)0);
}

void *fn_uptime(int init){
    if(init == 1 || _uptime_job == 0){
        // update clock every second
        _uptime_job = cron_add_job(0, 1, 0, 0, uptime_update_clock);
    }
    uptime_update_clock();
    while(1){
        frontbuttoncontrol_read();
        if(button_pressed){
            int val = frontbuttoncontrol_get_button();
            if(val == BUTTON_WHITE){
                // stop the job
                if(_uptime_job > 0){
                    cron_remove_job(_uptime_job);
                }
                _uptime_job = NULL;
                //leave
                break;
            }
        }
        if(lastSec != cron_seconds){
            lcd_gotoxy(0, 0);
            lcd_puts((const char *)buf_uptime_string);
            lcd_gotoxy(0, 1);
            lcd_puts(buf_systemtime_string);
            lastSec = cron_seconds;
        }
    }
    stopApplication();
    return((void *)0);
}