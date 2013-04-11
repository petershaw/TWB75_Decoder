//
//  hello.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//  Test function that demonstrate the basic useage of a function.
//  It will print out "Hello world." to the lcd and move a dash
//  from left to right and reverse
//  on the second line.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>

#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "hello.h"

int hello_position = 0;                     // position of -

void *fn_sayHello(int init){
    lcd_gotoxy(0, 0);
    lcd_puts(("hello world."));
    lcd_gotoxy(0, 2);
    lcd_puts(("                "));
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

