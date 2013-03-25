//
//  hello.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>

#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "hello.h"

int hello_position = 0;                     // position of -
char buf[3];                                // uart output buffer

void *fn_sayHello(void){
    lcd_puts(("hello world."));
    lcd_gotoxy(hello_position, 2);
    lcd_puts(" -");
    ++hello_position;
    if(hello_position > 15){
        hello_position = 0;
    }
    if(opt_send_data_via_uart){
        LIGHT_ON(LED_RED);
        itoa(hello_position, buf, 10);
        uart_puts( buf );
        uart_puts( "\n" );
        LIGHT_OFF(LED_RED);
    }
    _delay_ms(200);
    return (void *) NULL;
}

