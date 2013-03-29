//
//  saveeeprom.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/29/13.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>

#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "saveeeprom.h"

/**
 * Saving preferences to eeprom
 * This is a one shot application
 */
void *opt_save_preferences(void){
    LIGHT_ON(LED_RED);
    lcd_puts("Saveing data to\neeprom...\n");
    if(opt_send_data_via_uart){
        uart_puts("Saveing data to eeprom...\n");
    }
    save_preferences();
    lcd_clrscr();
    lcd_puts("done.");
    if(opt_send_data_via_uart){
        uart_puts("done.\n");
    }
    _delay_ms(1000);
    // turn the application off...
    isApplicationRunning = false;
    LIGHT_OFF(LED_RED);
    return NULL;
}

