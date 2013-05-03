//
//  frontbuttoncontrol.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#ifndef AnalyserDude_frontbuttoncontrol_h
#define AnalyserDude_frontbuttoncontrol_h

#include <stdbool.h>

#define BUTTON_BLUE     1
#define BUTTON_GREEN    2
#define BUTTON_YELLOW   3
#define BUTTON_WHITE    4

volatile bool button_pressed;
volatile bool button_listening;
volatile int  button_value;

void frontbuttoncontrol_init(void);
void frontbuttoncontrol_read(void);
 int frontbuttoncontrol_get_button(void);

#endif
