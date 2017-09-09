#pragma once
#ifndef INC_LIBG2FASTH_BASE_SUITE_H
#define INC_LIBG2FASTH_BASE_SUITE_H

#include "g2fasth_enums.hpp"
#include "thread_pool.h"

namespace g2 {
namespace fasth {
/**
* This class is base of all suites.
* It is not templated and therefore can be used by test agent.
*/
class base_suite {
    friend class test_agent;
    /**
    * This function initializes the test suite.
    * @param thread_pool Shared thread pool instance.
    */
    virtual void init(std::shared_ptr<tthread::thread_pool> thread_pool) {
        d_thread_pool = thread_pool;
    }
    /**
    * This function executes test suite. First it setups test track and then starts execution.
    * @param report_file_name Absolute path of the JUnit report xml, can be empty if report is not to be written.
    * @return JUnit report in string format.
    */
    virtual std::string execute(std::string report_file_name = "") {
        return "";
    };
    virtual void set_state(test_run_state new_state) {}
    virtual test_run_state state() { return not_yet; }
protected:
    /**
    * Constructor that sets the name of the suite.
    * @param suite_name name of the test suite.
    */
    base_suite(std::string suite_name)
        : d_suite_name(suite_name) {
    }
public:
    /**
    * This function returns name of the suite.
    * @return name of the test suite.
    */
    inline const std::string& get_suite_name() {
        return d_suite_name;
    }
protected:
    std::shared_ptr<tthread::thread_pool> d_thread_pool;
private:
    std::string d_suite_name;
};
}
}

#endif // !INC_LIBG2FASTH_BASE_SUITE_H