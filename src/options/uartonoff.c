//
//  uartonoff.c
//  AnalyserDude
//
//  Created by Kris Wolff on 3/19/13.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"
#include "../control/frontbuttoncontrol.h"

#include "uartonoff.h"

bool opt_send_data_via_uart_lastvalue = false;

void *opt_uartonoff_init(int init){
    frontbuttoncontrol_read();
    if(opt_send_data_via_uart_lastvalue != opt_send_data_via_uart){
        lcd_gotoxy(0, 2);
        if(opt_send_data_via_uart == false){
            lcd_puts("Uart turned off");
        } else {
            lcd_puts("Uart turned on ");
        }
    }
    
    if(frontbuttoncontrol_get_button() == BUTTON_BLUE){
        opt_send_data_via_uart = !opt_send_data_via_uart;
        if(opt_send_data_via_uart){
            LIGHT_ON(LED_RED);
            _delay_ms(300);
            uart_puts("Starts to send data:\n");
            LIGHT_OFF(LED_RED);
        } else {
            LIGHT_ON(LED_RED);
            _delay_ms(300);
            uart_puts("Stop sending data.\n");
            LIGHT_OFF(LED_RED);
        }
        _delay_ms(700);
    }
    return NULL;
}


