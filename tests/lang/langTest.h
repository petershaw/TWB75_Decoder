#include "../cu/cu.h"


// Declarations of tests
TEST(testRead);
TEST(testSet);

// Collect tests into test suite
TEST_SUITE(LANG_TEST) {
    TEST_ADD(testRead),
    TEST_ADD(testSet),
    TEST_SUITE_CLOSURE
};

