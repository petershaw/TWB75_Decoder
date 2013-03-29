//
//  main.c
//  AnalyserDude
//
//  Created by Peter Shaw
//  Copyright (c) 2013. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "global.h"
#include "device/deviceconfig.h"
#include "ui/lights.h"
#include "ui/menu.h"
#include "control/frontbuttoncontrol.h"

#include "options/uartonoff.h"
#include "options/saveeeprom.h"

#include "functions/hello.h"
#include "functions/countExtPorts.h"
#include "functions/countFastPorts.h"
#include "functions/showDACValue.h"

// DUMMY FUNCTION
// ---------------------------------------------
void *dummy(void){return (void *) NULL;};

// GLOBAL OPTIONS
// ---------------------------------------------
// see deviceconfig.h

int main(void) {
    //initialize the device
    device_init();
    _delay_ms(1000);                    // wait for 1sec
    device_reset();
    
    ui_menu_init();
    ui_menu_add("Say Hello", fn_sayHello );
    ui_menu_add("Count ext ports", fn_countExtPorts );
    //    ui_menu_add((char *)"Count fast ports", (void *)fn_countFastPorts );
    ui_menu_add("Show DAC values", fn_showDACValue );
    menuentry_t *optionsMenu = ui_menu_add("Options:\n(Submenu)", dummy );
    ui_menu_add_sub(optionsMenu, "Send data via\nUART", opt_uartonoff_init );
    ui_menu_add_sub(optionsMenu, "Save Preferences", opt_save_preferences );
    
    ui_menu_show();
    
    // set the lights
    LIGHT_OFF(LED_RED);
    LIGHT_OFF(LED_GREEN);
    
    frontbuttoncontrol_init();
    
    // mainloop
    while(1) {
        frontbuttoncontrol_read();
        if(button_pressed && button_listening){
            int val = frontbuttoncontrol_get_button();
            
            // pageing
            if(val == BUTTON_BLUE){
                ui_menu_next();
                ui_menu_show();
            }
            // execute
            if(val == BUTTON_GREEN){
                // if no submenu is available than run the application, otherwise go into the submenu
                if(ui_menu_has_submenu()){
                    ui_menu_enter_submenu();
                    ui_menu_show();
                } else {
                    button_listening = false;
                    isApplicationRunning = true;
                    ui_menu_run();
                }
            }
            // leaving submenu
            if(val == BUTTON_WHITE){
                //if(ui_menu_has_submenu() == true){
                    ui_menu_leave_submenu();
                    ui_menu_show();
                //}
            }
            _delay_ms(200);
        }
        if(button_pressed && button_value == BUTTON_WHITE && button_listening == false){
            // escape sequence
            isApplicationRunning = false;
            LIGHT_OFF(LED_GREEN);
            ui_menu_show();
            button_listening = true;
        }
        
        if(isApplicationRunning){ 
          ui_menu_run();
        }
        
    }

}
