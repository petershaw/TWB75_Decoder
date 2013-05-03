//
//  showDACValue.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//
//  Show the values of the both analog input in 10Bit resolution.
//  From 0 (0 Volts) - 1023 (5 Volts)
//

#include <stdio.h>

#include "../../src-lib/lcd/lcd.h"
#include "../../src-lib/uart/uart.h"

#include "../global.h"
#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "showDACValue.h"


volatile int dacValue_1 = 0;
 int dacValue_2 = 0;

char buf_dac_values[16] = "";

void sampleDACPorts_read(void){
    ADCSRA = (1<<ADEN)                      // enable ADC
    | (1<<ADPS2)                            // set 128 to the prescaller
    | (1<<ADPS1)
    | (1<<ADPS0);
    
	ADMUX = 5;                              // set the channel (on the psen-board it's: 5
	ADCSRA |= (1<<ADSC);                    //  to start the conversion
    while(ADCSRA & (1<<ADSC));              // wait for results
    dacValue_1 = ADCW;                      // get the 10bit value from ADCL + ADCH

    ADMUX = 4;                              // set the channel (on the psen-board it's: 5
	ADCSRA |= (1<<ADSC);                    //  to start the conversion
    while(ADCSRA & (1<<ADSC));              // wait for results
    dacValue_2 = ADCW;                      // get the 10bit value from ADCL + ADCH

	
	ADCSRA &= ~(1<<ADEN);                   // disable ADC
}

void *fn_showDACValue(int init){
    // display the application screen
    lcd_puts(("DAC 1      DAC 2"));
    lcd_gotoxy(0, 2);
    sprintf(buf_dac_values, " %4d       %4d", dacValue_1, dacValue_2);
    lcd_puts(buf_dac_values);

    if(opt_send_data_via_uart){
        LIGHT_ON(LED_RED);
        sprintf(buf_dac_values, "%d,%d;\n", dacValue_1, dacValue_2);
        uart_puts( buf_dac_values );
        uart_puts("\n");
        LIGHT_OFF(LED_RED);
    }

    // count the ports
    sampleDACPorts_read();
    return (void *) NULL;
}
