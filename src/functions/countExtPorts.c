//
//  countExtPorts.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#include <stdio.h>
#include <stdbool.h>

#include "../device/deviceconfig.h"
#include "../ui/lights.h"

#include "countExtPorts.h"

int cntBlue = 0;
int cntGreen = 0;
int cntYellow = 0;
int cntWhite = 0;

bool isActiveBlue = false;
bool isActiveGreen = false;
bool isActiveYellow = false;
bool isActiveWhite = false;

char buf_cnt_ext_ports[16] = "";

void countExtPorts_read(void){
    PISO_INHIBIT_PORT |= PISO_INHIBIT_PIN;                  // Disable clock listener
    
    PISO_CLOCK_PORT |= PISO_CLOCK_PIN;                      // turn clock high
    PISO_LOAD_PORT  &= ~PISO_LOAD_PIN;                      // LOW on LOAD -> load the register
    PISO_LOAD_PORT  |= PISO_LOAD_PIN;                       // HIGH on LOAD
    
    PISO_CLOCK_PORT &= ~PISO_CLOCK_PIN;                     // turn clock low
    PISO_INHIBIT_PORT &= ~PISO_INHIBIT_PIN;
    
    int i;
    int a;                                                  // current value
    int r = 0;                                              // result button number
    for(i=0; i<4; i++){
        a = 0;
        if(PISO_OUTPUT_PORT & (1<<PISO_OUTPUT_PIN_NAME)){   // welcher wert steht in PINB & (1<<PB4)?
            a = a >> 2 ^(i+1);                              // Pressed!
        }
        r = r + (a);
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;                  // toggle clock -- shift the register
        PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;
    }
    
    if(r == 1 && !isActiveBlue){
        isActiveBlue = true;
        ++cntBlue;
    } else if(r == 2 && !isActiveGreen){
        isActiveGreen = true;
        ++cntGreen;
    } else if(r == 3 && !isActiveYellow){
        isActiveYellow = true;
        ++cntYellow;
    } else if(r == 4 && !isActiveWhite){
        isActiveWhite = true;
        ++cntWhite;
    }
    
    if(r != 1 && isActiveBlue){
        isActiveBlue = false;
    } else if(r != 2 && isActiveGreen){
        isActiveGreen = false;
    } else if(r != 3 && isActiveYellow){
        isActiveYellow = false;
    } else if(r != 4 && isActiveWhite){
        isActiveWhite = false;
    }
    
    if(opt_send_data_via_uart){
        LIGHT_ON(LED_RED);
        
        LIGHT_OFF(LED_RED);
    }
    
}

void countExtPorts_resetOnOverflow(void){
    if(cntBlue > 9999){
        cntBlue = 0;
    }
    if(cntGreen > 9999){
        cntGreen = 0;
    }
    if(cntYellow > 9999){
        cntYellow = 0;
    }
    if(cntWhite > 9999){
        cntWhite = 0;
    }
}

void *fn_countExtPorts(void){
    // display the application screen
    lcd_puts("BLU GRN YEL WHI");
    lcd_gotoxy(0, 2);
    sprintf(buf_cnt_ext_ports, "%3d %3d %3d %3d", cntBlue, cntGreen, cntYellow, cntWhite);
    lcd_puts(buf_cnt_ext_ports);
    if(opt_send_data_via_uart){
        LIGHT_ON(LED_RED);
        itoa(cntBlue, buf_cnt_ext_ports, 10);
        uart_puts( buf_cnt_ext_ports );
        uart_puts( ",");
        itoa(cntGreen, buf_cnt_ext_ports, 10);
        uart_puts( buf_cnt_ext_ports );
        uart_puts( "," );
        itoa(cntYellow, buf_cnt_ext_ports, 10);
        uart_puts( buf_cnt_ext_ports );
        uart_puts( "," );
        itoa(cntWhite, buf_cnt_ext_ports, 10);
        uart_puts( buf_cnt_ext_ports );

        LIGHT_OFF(LED_RED);
    }
    // count the ports
    countExtPorts_resetOnOverflow();
    countExtPorts_read();
    return (void *) NULL;
}