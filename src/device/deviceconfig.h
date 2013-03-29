//
//  deviceconfig.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#ifndef AnalyserDude_deviceconfig_h
#define AnalyserDude_deviceconfig_h

#include <stdio.h>
#ifndef IGNOREINTESTS
#include <avr/io.h>
#endif

// DEFINE SOFTWARE VERSION
// ---------------------------------------------
#define VERSION_STRING                  "1.0"

// DEFINE THE LEDs
// Section control led configuration
// ---------------------------------------------
#define LED_DATA_DIRECTION_REGISTER     DDRB
#define LED_RED                         0b00000001          // PIN Register for the red led
#define LED_GREEN                       0b00000010          // PIN Register for the green led

// DEFINE THE INPUTS
// Section define fast digital inputs
// ---------------------------------------------
#define DIGITAL_IN_1_DATA_DIRECTION_REGISTER   DDRB
#define DIGITAL_IN_1_PORT      PORTB
#define DIGITAL_IN_1_PIN       PB2                          // PB.2
#define DIGITAL_IN_1_READ      PINB

#define DIGITAL_IN_2_DATA_DIRECTION_REGISTER   DDRD
#define DIGITAL_IN_2_PORT      PORTD
#define DIGITAL_IN_2_PIN       PD7                          // PD.7
#define DIGITAL_IN_2_READ      PIND

// DEFINE THE OUTPUTS
// ---------------------------------------------

// DEFINE THE PISO SHIFT REGISTER
// ---------------------------------------------
#define PISO_DATA_DIRECTION_REGISTER    DDRD
#define PISO_CLOCK_PORT                 PORTD
#define PISO_CLOCK_PIN                  0b00001000         // SR .pin  2

#define PISO_INHIBIT_PORT               PORTD
#define PISO_INHIBIT_PIN                0b00010000         // SR .pin 15

#define PISO_LOAD_PORT                  PORTD
#define PISO_LOAD_PIN                   0b00000100         // SR .pin  1

#define PISO_OUTPUT_PORT                PINB
#define PISO_OUTPUT_PIN                 0b00010000         // SR .pin  9
#define PISO_OUTPUT_PIN_NAME            PB4         

// DEFINE THE EEPROM
// ---------------------------------------------
#define EEPROM_ADRESS_PREFERENCES       (0x00)            // First Cell

// DEFINE COMMUNICATION SPEED
// ---------------------------------------------
#define UART_BAUD_RATE                  9600

// PREFERENCES
// ---------------------------------------------
#define PREFERENCE_UART_DATA            1
#define PREFERENCE_DEBUG_MODE           2

// API
// ---------------------------------------------
void device_init(void);

void device_reset(void);

void save_preferences(void);

#endif
