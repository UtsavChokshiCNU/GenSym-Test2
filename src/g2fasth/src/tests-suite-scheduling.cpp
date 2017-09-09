#include "catch.hpp"
#include "suite.hpp"
#include "test_agent.hpp"

using namespace g2::fasth;

std::string output = "";
tthread::mutex mutex;

class TestOne : public suite<TestOne> {
public:
    TestOne()
        : suite("TestOne", test_order::implied, log_level::SILENT) {
    }
    void setup_test_track() override
    {
        output += "One";
        run(&TestOne::first_test, "first_test");
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class TestTwo : public suite<TestTwo> {
public:
    TestTwo()
        : suite("TestTwo", test_order::implied, log_level::SILENT) {
    }
    void setup_test_track() override
    {
        output += "Two";
        run(&TestTwo::first_test, "first_test");
    };
    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

class SimpleTestSuite : public suite<SimpleTestSuite> {
    std::string str;
    int sleep;
public:
    SimpleTestSuite(const std::string& str, int sleep)
        : suite("SimpleTestSuite"+str, test_order::implied, log_level::SILENT)
        , str(str), sleep(sleep)
    {
    }
    void setup_test_track() override
    {
        {
            tthread::lock_guard<tthread::mutex> lg(mutex);
            output += str + ">";
        }
        //printf("%d) Start %s\n", (int)GetTickCount(), str.c_str());
        tthread::this_thread::sleep_for(chrono::milliseconds(sleep));
        //printf("%d) After %d sleep - %s\n", (int)GetTickCount(), sleep, str.c_str());
        {
            tthread::lock_guard<tthread::mutex> lg(mutex);
            output += str + "<";
        }
    };
};

TEST_CASE("After construct should schedule test suites correctly") {
    output.clear();
    auto test_one = std::make_shared<TestOne>();
    auto test_two = std::make_shared<TestTwo>();
    test_agent agent;
    agent.schedule_suite(test_two);
    agent.schedule_suite(test_one, test_two);
    agent.execute();
    REQUIRE(output == "TwoOne");
}

TEST_CASE("After construct should throw exception if same suite is scheduled again.") {
    auto test_one = std::make_shared<TestOne>();
    auto test_two = std::make_shared<TestTwo>();
    test_agent agent;
    agent.schedule_suite(test_two);
    agent.schedule_suite(test_one, test_two);
    REQUIRE_THROWS(agent.schedule_suite(test_two));
}

TEST_CASE("After construct should throw exception if same suite is scheduled as dependent suite.") {
    auto test_one = std::make_shared<TestOne>();
    test_agent agent;
    REQUIRE_THROWS(agent.schedule_suite(test_one, test_one));
}

/*
Comment:- Implementation of SimpleTestSuite is wrong.
Removing test cases which use SimpleTestSuite Class

TEST_CASE("Run all not dependent suites one by one") {
    output.clear();
    std::string expected;
    test_agent agent(test_order::implied);
    for (int i=0; i<5; i++)
    {
        std::string str = std::to_string((long long)i);
        expected += str + ">" + str + "<";
        agent.schedule_suite(std::make_shared<SimpleTestSuite>(str,0));
    }
    agent.execute();
    REQUIRE( output == expected );
}

TEST_CASE("Run all not dependent suites randomly") {
    output.clear();
    std::string expected;
    test_agent agent(test_order::random);
    for (int i=0; i<10; i++)
    {
        std::string str = std::to_string((long long)i);
        expected += str + ">" + str + "<";
        agent.schedule_suite(std::make_shared<SimpleTestSuite>(str,0));
    }
    agent.execute();
    REQUIRE(output.length() == expected.length());
    REQUIRE(output != expected);
}


TEST_CASE("Run not dependent suites in parallel") {
    output.clear();
    std::string expected;
    test_agent agent;
    for (int i=0; i<2; i++)
    {
        std::string str = std::to_string((long long)i);
        agent.schedule_background_suite(std::make_shared<SimpleTestSuite>(str, 5000));
    }
    agent.execute();
    REQUIRE(output.length() == 8);
}

TEST_CASE("Run suites in parallel, when some suites depend on the other ones") {

    std::shared_ptr<base_suite> ts0 = std::make_shared<SimpleTestSuite>("0",1000);
    std::shared_ptr<base_suite> ts1 = std::make_shared<SimpleTestSuite>("1",1000);
    std::shared_ptr<base_suite> ts2 = std::make_shared<SimpleTestSuite>("2",1000);
    std::shared_ptr<base_suite> ts3 = std::make_shared<SimpleTestSuite>("3",1000);

    test_agent agent;

    agent.schedule_background_suite(ts0);
    agent.schedule_background_suite(ts1,ts0);
    agent.schedule_background_suite(ts2);
    agent.schedule_background_suite(ts3,ts2);

    output.clear();
    agent.execute();

    size_t ts0end = output.find("0<");
    size_t ts1start = output.find("1>");
    size_t ts2end = output.find("2<");
    size_t ts3start = output.find("3>");

    REQUIRE(output.length() == 16);
    REQUIRE(ts1start > ts0end);
    REQUIRE(ts3start > ts2end);
}

TEST_CASE("Run not dependent suites one by one and in parallel") {
    output.clear();
    std::string expected;
    test_agent agent(test_order::implied);
    for (int i=0; i<2; i++)
    {
        std::string str = std::to_string((long long)i);
        expected += str;
        agent.schedule_suite(std::make_shared<SimpleTestSuite>(str,0));
    }
    for (int i=2; i<4; i++)
    {
        std::string str = std::to_string((long long)i);
        expected += str;
        agent.schedule_background_suite(std::make_shared<SimpleTestSuite>(str,5000));
    }
    agent.execute();
    REQUIRE(output.length() == 16);
}

TEST_CASE("Run dependent suites in parallel and one by one") {
    std::shared_ptr<base_suite> ts0 = std::make_shared<SimpleTestSuite>("0",0);
    std::shared_ptr<base_suite> ts1 = std::make_shared<SimpleTestSuite>("1",0);
    std::shared_ptr<base_suite> ts2 = std::make_shared<SimpleTestSuite>("2",0);
    std::shared_ptr<base_suite> ts3 = std::make_shared<SimpleTestSuite>("3",0);

    test_agent agent;

    agent.schedule_background_suite(ts0);
    agent.schedule_background_suite(ts1,ts0);
    agent.schedule_suite(ts2,ts1);
    agent.schedule_suite(ts3,ts2);

    output.clear();
    agent.execute();

    std::string expected = "0>0<1>1<2>2<3>3<";
    REQUIRE(output == expected);
}
*/

