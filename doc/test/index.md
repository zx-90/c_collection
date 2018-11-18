# Unit tests

## Create test

For creating tests it need to include test and add `TEST` macros. Here is the minimal requires to create unit test:

    #include "test/test.h"
    
    TEST(Test description)
    {
        // Write your test here...
    }

Macros `TEST` define test function and adding handle function for this test. There is variable `test_result` which is parameter of test function. This variable has type `_Bool*` and return the result of test. So, you can handly set test with succes (`*test_result = 1`) or fail (`*test_result = 0`) status.

Also in `test/test.h` defined the next macros using in test functions:

Check conditions:

    TEST_ASSERT(condition);

Mark test as success and exit:

    TEST_SUCCESS

Mark Test as fail and exit:

    TEST_FAIL
    
## Run tests

Program for running tests:

    #define TEST_MAIN
    #include "test/test_main.h"

This header file adds function for register test in test list and add main function. You don't need include modules with unit tests in main file. Everything will do handle functions in `TEST` macros. You just need to control that all modules with unit tests are added to bin file.
