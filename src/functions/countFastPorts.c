//
//  countFastPorts.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#include <stdio.h>

#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "../device/deviceconfig.h"

#include "countFastPorts.h"

volatile int cnt_1 = 0;
volatile int cnt_2 = 0;
volatile int value_1 = 0;
volatile int value_2 = 0;

char buf_fdi_values[16];

void *fn_countFastPorts(void){
    // display the application screen
    lcd_puts("Digi 1   Digit 2");
    lcd_gotoxy(0, 2);
    sprintf(buf_fdi_values, "%3d       %3d", value_1, value_2);
    lcd_puts(buf_fdi_values);
    
    // count the ports
   
    value_1 = DIGITAL_IN_1_PIN;
    value_2 = DIGITAL_IN_2_PIN;
    return (void *) NULL;
}
