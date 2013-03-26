#include "../cu/cu.h"


// Declarations of tests
TEST(testPref);

// Collect tests into test suite
TEST_SUITE(LANG_TEST) {
    TEST_ADD(testPref),
    TEST_SUITE_CLOSURE
};

