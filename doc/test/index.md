# Unit tests

## Create test

For creating tests it need to include test and add `ZX_TEST` macros. Here is the minimal requires to create unit test:

    #include "test/test.h"
    
    ZX_TEST(Test description)
    {
        // Write your test here...
    }

Macros `ZX_TEST` define test function and adding handle function for this test. There is variable `test_result` which is parameter of test function. This variable has type `_Bool*` and return the result of test. So, you can handly set test with succes (`*test_result = 1`) or fail (`*test_result = 0`) status.

Also in `test/test.h` defined the next macros using in test functions:

Check conditions:

    ZX_TEST_ASSERT(condition);

Mark test as success and exit:

    ZX_TEST_SUCCESS

Mark Test as fail and exit:

    ZX_TEST_FAIL

Function `zx_test_all` runs all tests created by `ZX_TEXT` macros. Returns count of failed tests.

    int
    zx_test_all()

## Run tests

Simple program for running tests:

    #include "test/test_main.h"
    
    int
    main(void)
    {
        return zx_test_all();
    }

