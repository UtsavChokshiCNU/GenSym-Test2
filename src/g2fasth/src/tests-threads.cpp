#include "catch.hpp"
#include "suite.hpp"
#include "test_agent.hpp"

using namespace g2::fasth;


class ThreadTestSuite : public suite<ThreadTestSuite> {
    int test_case_number;
public:
    ThreadTestSuite(const std::string& str, int tc_number, bool parallel=true)
        : suite("SUITE-"+str, test_order::implied, log_level::SILENT), test_case_number(tc_number)
    {
        set_parallel(parallel);
    }
    void setup_test_track() override
    {
        for (int i=1; i<=test_case_number; i++)
            run(&ThreadTestSuite::test_case, "TEST"+std::to_string((long long)i));
    };
    void test_case(const std::string& tc_name)
    {
        tthread::this_thread::sleep_for(chrono::milliseconds(100));
        complete_test_case(tc_name, test_outcome::pass);
    }
};

TEST_CASE("Background suites, parallel cases, default concurrency") {
    test_agent agent;
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<ThreadTestSuite>(str,4));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Background suites, sequential cases, default concurrency") {
    test_agent agent;
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<ThreadTestSuite>(str,4,false));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Not background suites, parallel cases, default concurrency") {
    test_agent agent;
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_suite(std::make_shared<ThreadTestSuite>(str,4));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Background suites, parallel cases, increased concurrency") {
    test_agent agent;
    agent.set_concurrency(agent.concurrency()*3/2);
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<ThreadTestSuite>(str,4));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Background suites, parallel cases, maximum concurrency") {
    test_agent agent;
    REQUIRE_THROWS(agent.set_concurrency(1000));
}

TEST_CASE("Background suites, parallel cases, concurrency = 2") {
    test_agent agent;
    agent.set_concurrency(2);
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<ThreadTestSuite>(str,4));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Background suites, parallel cases, concurrency = 1") {
    test_agent agent;
    agent.set_concurrency(1);
    int count = 3;
    for (int i=1; i<=count; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<ThreadTestSuite>(str,4));
    }
    timing start;
    agent.execute();
    REQUIRE(agent.concurrency_used() <= agent.concurrency());
}

TEST_CASE("Setting the too large concurrency value") {
    test_agent agent;
    REQUIRE_THROWS(agent.set_concurrency(agent.concurrency()*4));
}
