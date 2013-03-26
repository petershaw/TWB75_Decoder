//
//  deviceconfig.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#include <stdio.h>
#include <stdbool.h>

#ifndef IGNOREINTESTS
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#endif

#ifndef IGNOREINTESTS
#include "../../src-lib/uart/uart.h"
#include "../../src-lib/lcd/lcd.h"
#endif

#include "../global.h"
#include "deviceconfig.h"

char EEMEM preferences_settings;

/**
 * Restores the saved preferences from the eeprom 
 */
void restore_preferences(void){
    char pref;
    pref = eeprom_read_byte(&preferences_settings);
    
    if(pref & PREFERENCE_UART_DATA == PREFERENCE_UART_DATA) {
        opt_send_data_via_uart = true;
    }
}

/**
 * Initialize the lcd and printout a welcome message 
 */
void initialize_lcd(void){
    lcd_init(LCD_DISP_ON);                                          // initialize display, cursor off
    
    lcd_puts(":WELCOME TO THE:\n");                                 // welcome message
    lcd_puts("AnalyserDude ");
    lcd_puts(VERSION_STRING);
}

/**
 * Initialize the piso shift register for reading 
 */
void initialize_piso(void){
    PISO_DATA_DIRECTION_REGISTER |= PISO_CLOCK_PIN;
    PISO_DATA_DIRECTION_REGISTER |= PISO_INHIBIT_PIN;
    PISO_DATA_DIRECTION_REGISTER |= PISO_LOAD_PIN;
    PISO_DATA_DIRECTION_REGISTER &= ~(1<<PISO_OUTPUT_PIN);          //  INPUT pin
    
    PISO_CLOCK_PORT &= ~PISO_CLOCK_PIN;                             // CLOCK OFF
    PISO_LOAD_PORT  |= PISO_LOAD_PIN;                               // LOAD ON
    PISO_INHIBIT_PORT &= ~PISO_INHIBIT_PIN;                         // INHIBIT OFF
}

/** 
 * Initialize the fast digital lane
 */
void initialize_fast_digital(void){
//    DIGITAL_IN_1_DATA_DIRECTION_REGISTER ^= (1 << DIGITAL_IN_1_PIN);
//    DIGITAL_IN_1_DATA_DIRECTION_REGISTER ^= (1 << DIGITAL_IN_2_PIN);
}

void initialize_uart(void){
    uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
}

/**
 * initalise the device. Setup Ports and Pins, Buttons and Leds
 * also initialize the display.
 */
void device_init(void){
    // All applications are stoped
    isApplicationRunning = false;
    
    // startup lcd
    initialize_lcd();
    
    // initialize the piso shift register. This register contorols inputs from the
    // four frontbuttons and the four digital inputs 0001 - 1000
    initialize_piso();
    
    // initialize the fast digital ports
   initialize_fast_digital();
    
    // initialize the uart port
    initialize_uart();
    
    // set the device leds
    LED_DATA_DIRECTION_REGISTER |= 3; // 0b00000011;                                       // set up pin direction PortB as Output
    
    // read preferences from eeprom
    restore_preferences();
    
    // enable the interrupts
    sei();

}

/**
 * Resets the device. 
 * Clear all inputs and outputs
 */
void device_reset(void){
    // clear lcd
    lcd_clrscr();
    
}