#include "../cu/cu.h"


// Declarations of tests
TEST(testTimerInit);
TEST(testTimerTick);
TEST(testTimerOverclock);
TEST(testTimerGetTime);


// Collect tests into test suite
TEST_SUITE(TIMER_TEST) {
    TEST_ADD(testTimerInit),
    TEST_ADD(testTimerTick),
    TEST_ADD(testTimerOverclock),
    TEST_ADD(testTimerGetTime),
    TEST_SUITE_CLOSURE
};

