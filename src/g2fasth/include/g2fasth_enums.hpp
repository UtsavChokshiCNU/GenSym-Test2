#pragma once
#ifndef INC_LIBG2FASTH_TEST_ORDER_H
#define INC_LIBG2FASTH_TEST_ORDER_H

namespace g2 {
namespace fasth {
/**
* This enum is used to configure test execution order.
*/
enum test_order {
    random,
    implied
};

/**
* This enum is used as test outcome of executed test cases.
*/
enum test_outcome {
    fail,
    pass
};

static const char* test_outcome_str[] = { "Fail", "Pass" };

/**
* This enum tells current state of test execution.
*/
enum test_run_state {
    not_yet,
    ongoing,
    done
};

/**
* This enum controls the level of logging to be done.
*/
enum log_level
{
    // Logs nothing.
    NONE,
    // Logs only start and end of test suite execution.
    SILENT,
    // Logs start and end of test suite as well as each test case within it.
    REGULAR,
    // Logs everything.
    VERBOSE
};
}
}

// This is an ugly place to put it in, but it's a temporary
// solution until we remove the shackles of GCC 4.6, which
// doesn't support C++11 keyword `override`
#if (__GNUC__ < 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ < 7))
#define override
#endif

#endif // !INC_LIBG2FASTH_TEST_ORDER_H