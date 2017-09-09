#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

void test_case_fail_thread(void* p);

class TestAsyncScenarios : public suite<TestAsyncScenarios> {
public:
    struct thread_data
    {
        TestAsyncScenarios* suite;
        std::string test_case_name;
    };
    TestAsyncScenarios()
        : suite("TestAsync", test_order::implied, log_level::NONE) {
		set_parallel(false);
    };
    ~TestAsyncScenarios()
    {
        while (threads.size())
        {
            std::shared_ptr<tthread::thread> thread = threads.front();
            threads.pop_front();
            thread->join();
        }
    }
    void setup_test_track_scenario1()
    {
        run(&TestAsyncScenarios::first_test, "first_test");
    };
    void setup_test_track_scenario2()
    {
        run(&TestAsyncScenarios::first_test, "first_test");
        run(&TestAsyncScenarios::second_test, "second_test").after_success_of(&TestAsyncScenarios::first_test);
    };
    void setup_test_track_scenario3()
    {
        run(&TestAsyncScenarios::first_test, "first_test");
        run(&TestAsyncScenarios::third_test, "third_test").after_success_of(&TestAsyncScenarios::first_test);
    };
    void setup_test_track_scenario4()
    {
        run(&TestAsyncScenarios::third_test, "third_test");
        run(&TestAsyncScenarios::first_test, "first_test").after_success_of(&TestAsyncScenarios::third_test);
    };
    void setup_test_track_scenario5()
    {
        run(&TestAsyncScenarios::second_test, "second_test");
        run(&TestAsyncScenarios::first_test, "first_test").after_success_of(&TestAsyncScenarios::second_test);
    };
    void first_test(const std::string& test_case_name)
    {
        output += "<A>";
        // Go async with TestAsyncScenarios::first_test_func_obj()
        go_async(test_case_name, &TestAsyncScenarios::first_test_func_obj);
    }
    void second_test(const std::string& test_case_name)
    {
        std::unique_ptr<thread_data> data(new thread_data);
        data->suite = this;
        data->test_case_name = test_case_name;

        output += "<B>";
        std::shared_ptr<tthread::thread> ptr = std::make_shared<tthread::thread>(test_case_fail_thread, data.release());
        threads.push_back(ptr);
    }
    void third_test(const std::string& test_case_name)
    {
        output += "<C>";
        // Complete test case
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void first_test_func_obj(const std::string& test_case_name)
    {
        tthread::this_thread::sleep_for(tthread::chrono::milliseconds(1000));
        // Complete test case
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void test_async_itself(const std::string& test_case_name)
    {
        output += "<ENTER>";
        static bool async = false;
        if (!async)
        {
            async = true;
            output += "<SYNC>";
            return go_async(test_case_name);
        }
        output += "<ASYNC>";
        complete_test_case(test_case_name, test_outcome::pass);
    }
    std::string output;
    std::list<std::shared_ptr<tthread::thread>> threads;
};

TEST_CASE("Test Suite should run async test in finite time") {
    TestAsyncScenarios test_async;
    test_async.setup_test_track_scenario1();
    test_async.execute();
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(2000));
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Test Suite should run dependent async test in finite time") {
    TestAsyncScenarios test_async;
    test_async.setup_test_track_scenario2();
    test_async.execute();
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
    REQUIRE(results[1].outcome() == test_outcome::fail);
}

TEST_CASE("Sync test should run only when dependent async test has finished executing.") {
    TestAsyncScenarios test_async;
    test_async.setup_test_track_scenario3();
    test_async.execute();
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
    REQUIRE(results[1].outcome() == test_outcome::pass);
    REQUIRE(test_async.output == "<A><C>");
}

TEST_CASE("Async test should run only when dependent sync test has executed.") {
    TestAsyncScenarios test_async;
    test_async.setup_test_track_scenario4();
    test_async.execute();
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
    REQUIRE(results[1].outcome() == test_outcome::pass);
    REQUIRE(test_async.output == "<C><A>");
}

TEST_CASE("Test should fail and not execute if dependent method (after_sccess_of) fails.") {
    TestAsyncScenarios test_async;
    test_async.setup_test_track_scenario5();
    test_async.execute();
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
    REQUIRE(results[1].outcome() == test_outcome::fail);
    REQUIRE(test_async.output == "<B>");
}

void test_case_fail_thread(void* p)
{
    std::unique_ptr<TestAsyncScenarios::thread_data> data((TestAsyncScenarios::thread_data*)p);

    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(1000));
    // Complete test case
    data->suite->complete_test_case(data->test_case_name, test_outcome::fail);
}

TEST_CASE("Async test with initial test case as async functional object.") {
    TestAsyncScenarios test_async;
    test_async.run(&TestAsyncScenarios::test_async_itself, "test_async_itself");
    test_async.execute();
    auto results = test_async.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
    REQUIRE(test_async.output == "<ENTER><SYNC><ENTER><ASYNC>");
}

