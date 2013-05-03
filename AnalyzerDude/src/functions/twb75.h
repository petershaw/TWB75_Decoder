
#ifndef twb75_h
#define twb75_h

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

char twb_finischseq;
char twb_startseq;
char twb_stopseq;

uint8_t twb_current_value;
uint8_t twb_current_charackter_position;
char    twb_buffer[16];

bool    twb_is_port_active;
bool    twb_is_sequ_active;

void *fn_twb75(int init);

#endif
