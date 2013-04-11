//
//  timeoutTest.h
//  AnalyserDude
//
//  Created by Peter Shaw on 4/10/13.
//
//

#ifndef AnalyserDude_timeoutTest_h
#define AnalyserDude_timeoutTest_h

#include "../cu/cu.h"

int timeoutInvoked;

// Declarations of tests
TEST(testCronTimeoutAdd);
TEST(testCronTimeoutRemove);
TEST(testCronTimeoutExecute);


// Collect tests into test suite
TEST_SUITE(CRON_TIMEOUT_TEST) {
    TEST_ADD(testCronTimeoutAdd),
    TEST_ADD(testCronTimeoutRemove),
    TEST_ADD(testCronTimeoutExecute),
    TEST_SUITE_CLOSURE
};



#endif
