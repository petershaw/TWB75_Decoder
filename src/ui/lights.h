//
//  lights.h
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#ifndef AnalyserDude_lights_h
#define AnalyserDude_lights_h

#define LIGHT_ON(l) (PORTB |= (l))
#define LIGHT_OFF(l) (PORTB &= ~(l))
#define LIGHT_TOGGLE(l) (PORTB ^= (l))

#endif
