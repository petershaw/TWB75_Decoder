// Include definition of test suites
#ifndef IGNOREINTESTS
#define IGNOREINTESTS 1
#endif

#include "menu/menuTest.h"

// This struct contains all test suites
TEST_SUITES {
    TEST_SUITE_ADD(UI_MENUTEST), // add T1 test suite
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[]) {
    // Set up directory where are stored files with outputs from test
    // suites
    CU_SET_OUT_PREFIX("regressions/");
    
    // Run all test suites
    CU_RUN(argc, argv);
    
    return 0;
}
