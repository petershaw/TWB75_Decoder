//
//  menuTest.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#include <stdio.h>
#include "../cu/cu.h"

#define PREF_A                            (1)
#define PREF_B                            (2)
#define PREF_C                            (4)
#define PREF_D                            (8)

TEST(testPref) {
    
    char rA;
    char rB;
    char rC;
    char rD;
    rA = 0;
    rB = 0;
    rC = 0;
    rD = 0;
    
    char pref = 5;                          // A + C
        
    if(pref & PREF_A == PREF_A) {
        rA = 1;
    }
    if(pref & PREF_B == PREF_B) {
        rB = 1;
    }
    if(pref & PREF_C == PREF_C) {
        rC = 1;
    }
    if(pref & PREF_D == PREF_D) {
        rD = 1;
    }

    assertTrue(1 == rA);
    assertTrue(0 == rB);
    assertTrue(1 == rC);
    assertTrue(0 == rD);
    
}
