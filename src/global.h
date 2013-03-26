//
//  global.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/10/13.
//
//

#ifndef AnalyserDude_global_h
#define AnalyserDude_global_h
#include <stdbool.h>

// GLOBAL MACROS
// ---------------------------------------------
#define READ(U, N)  ((U) >> (N) & 1u)
#define SET(U, N)   ((void)((U) |= 1u << (N)))
#define CLR(U, N)   ((void)((U) &= ~(1u << (N))))
#define FLIP(U, N)  ((void)((U) ^= 1u << (N)))

volatile bool isApplicationRunning;
bool opt_send_data_via_uart;
bool debug_mode;

void *dummy(void);

#endif
