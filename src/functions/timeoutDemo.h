//
//  timeoutDemo.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/31/13.
//
//

#ifndef AnalyserDude_timeoutdemo_h
#define AnalyserDude_timeoutdemo_h

#define ASCII_BEGIN_NUMBERS     48
#define timerDemo_TIMEOUT_ID    1

unsigned int timerDemo_current_value;
char timerDemoBuffer[9];
int timerDemo_last_button_pressed;
int timerDemo_current_charackter_position;

void *fn_timeoutDemo(int init);

#endif
