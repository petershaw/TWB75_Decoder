//
//  menuTest.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#include <stdio.h>
#include "../cu/cu.h"

#define PREF_A                            (1)   // 00000001
#define PREF_B                            (2)   // 00000010
#define PREF_C                            (4)   // 00000100
#define PREF_D                            (8)   // 00001000

// 10                                              00001010

TEST(testRead) {
    char rA;
    char rB;
    char rC;
    char rD;
    rA = 0;
    rB = 0;
    rC = 0;
    rD = 0;
    
    char pref = 5;                          // A + C

    if(pref & PREF_A ) {
        rA = 1;
    }
    if(pref & PREF_B ) {
        rB = 1;
    }
    if(pref & PREF_C) {
        rC = 1;
    }
    if(pref & PREF_D ) {
        rD = 1;
    }

    assertTrue(1 == rA);
    assertTrue(0 == rB);
    assertTrue(1 == rC);
    assertTrue(0 == rD);
}

TEST(testSet){
    char result;
    result = 0;
    
    assertTrue(0 == result);

    result = (result | PREF_B);
    result = (result | PREF_D);
    assertEquals(10 ,result);
    
}