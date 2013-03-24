//
//  frontbuttoncontrol.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>

#include "../device/deviceconfig.h"
#include "frontbuttoncontrol.h"

void piso_toggle_clock(void){
    PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;                  // toggle clock -- shift the register
    PISO_CLOCK_PORT ^= PISO_CLOCK_PIN;
}

void frontbuttoncontrol_init(void){
    button_pressed = false;
    button_listening = true;
    button_value = 0;
}

void frontbuttoncontrol_read(void){
    PISO_INHIBIT_PORT |= PISO_INHIBIT_PIN;                  // Disable clock listener
    
    PISO_CLOCK_PORT |= PISO_CLOCK_PIN;                      // turn clock high
    PISO_LOAD_PORT  &= ~PISO_LOAD_PIN;                      // LOW on LOAD -> load the register
    PISO_LOAD_PORT  |= PISO_LOAD_PIN;                       // HIGH on LOAD
    
    PISO_CLOCK_PORT &= ~PISO_CLOCK_PIN;                     // turn clock low
    PISO_INHIBIT_PORT &= ~PISO_INHIBIT_PIN;

    int i;
    int a;                                                  // current value
    int r = 0;                                                  // result button number
    for(i=0; i<4; i++){                                     // ignore the external pins
        piso_toggle_clock();
    }
    for(i=0; i<4; i++){                            
        a = 0;
        if(PISO_OUTPUT_PORT & (1<<PISO_OUTPUT_PIN_NAME)){   // welcher wert steht in PINB & (1<<PB4)?
            a = a >> 2 ^(i+1);                                // Pressed!
        }
        r = r + (a);
        piso_toggle_clock();
    }
    if(r != 0){
        button_value = r;
        button_pressed = true;
    }
}

int frontbuttoncontrol_get_button(void){
    int value = button_value;
    button_value = 0;
    button_pressed = false;
    return value;
}


