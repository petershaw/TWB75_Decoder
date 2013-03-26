//
//  menuTest.c
//  AnalyserDude
//
//  Created by Peter Shaw on 3/9/13.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CUnit/Basic.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_lang_init_01() {
    puts("test LANG");
    int i = 1;
    CU_ASSERT_EQUAL( 1, i);
}
