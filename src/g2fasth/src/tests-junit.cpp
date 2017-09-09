#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;
using namespace tinyxml2;

class TestJUnit : public suite<TestJUnit> {
public:
    TestJUnit()
        : suite("TestJUnit", test_order::implied, log_level::NONE)
        , first_test_should_fail(false){
    };
    void setup_test_track() override
    {
        run(&TestJUnit::first_test, "first_test");
    };
    void first_test(const std::string& test_case_name)
    {
        if (first_test_should_fail)
        {
            complete_test_case(test_case_name, test_outcome::fail);
        }
        else
        {
            complete_test_case(test_case_name, test_outcome::pass);
        }
    }
    bool first_test_should_fail;
};

TEST_CASE("Test Suite should return JUnit report after all success") {
    TestJUnit test_junit;
    auto report = test_junit.execute();
    XMLDocument doc;
    doc.Parse(report.c_str());
    std::string root_name = doc.RootElement()->Name();
    XMLElement* child = doc.RootElement()->FirstChildElement();
    std::string child_name;
    if (child)
        child_name = child->Name();
    auto results = test_junit.get_results();
    REQUIRE(root_name == "testsuite");
    REQUIRE(child_name == "testcase");
    REQUIRE(results.size() == 1);
    REQUIRE(results[0].outcome() == test_outcome::pass);
}

TEST_CASE("Test Suite should return JUnit report after some success") {
    TestJUnit test_junit;
    test_junit.first_test_should_fail = true;
    auto report = test_junit.execute();
    XMLDocument doc;
    doc.Parse(report.c_str());
    std::string root_name = doc.RootElement()->Name();
    XMLElement* child = doc.RootElement()->FirstChildElement();
    std::string child_name, fail_name;
    if (child)
    {
        child_name = child->Name();
        XMLElement* fail = child->FirstChildElement();
        if (fail)
            fail_name = fail->Name();
    }
    auto results = test_junit.get_results();
    REQUIRE(root_name == "testsuite");
    REQUIRE(child_name == "testcase");
    REQUIRE(fail_name == "failure");
    REQUIRE(results.size() == 1);
    REQUIRE(results[0].outcome() == test_outcome::fail);
}

class ReportTest : public suite<ReportTest> {
    int sleep;
public:
    ReportTest(int sleep)
        : suite("ReportTest", test_order::implied, log_level::NONE), sleep(sleep)
    {
        set_parallel(false);
    }
    void test(const std::string& test_case_name)
    {
        tthread::this_thread::sleep_for(chrono::milliseconds(sleep));
        complete_test_case(test_case_name, test_outcome::pass);
    }
};

TEST_CASE("Test case number") {
    ReportTest ts(200);

    int count = 5;
    for (int i=0; i<count; i++)
        ts.run(&ReportTest::test, std::to_string((long long)i));

    std::string report;
    report = ts.execute("");

    XMLDocument doc;
    doc.Parse(report.c_str());

    int rep_count = -1;
    int error = doc.RootElement()->QueryAttribute("tests", &rep_count);

    REQUIRE(XML_SUCCESS == error);
    REQUIRE(rep_count == count);
}

TEST_CASE("Test suite time stamp") {
    ReportTest ts(0);

    int count = 5;
    for (int i=0; i<count; i++)
        ts.run(&ReportTest::test, std::to_string((long long)i));

    std::string report;
    report = ts.execute("");

    XMLDocument doc;
    doc.Parse(report.c_str());

    const char* att = doc.RootElement()->Attribute("start");
    std::string time_stamp(att?att:"");

    REQUIRE(att != 0);
    REQUIRE(time_stamp.length() == 23);
}

TEST_CASE("Test suite elapsed time") {
    ReportTest ts(1000);

    int count = 5;
    for (int i=0; i<count; i++)
        ts.run(&ReportTest::test, std::to_string((long long)i));

    std::string report;
    report = ts.execute("");

    XMLDocument doc;
    doc.Parse(report.c_str());

    int elapsed = -1;
    int error = doc.RootElement()->QueryAttribute("elapsed", &elapsed);

    REQUIRE(XML_SUCCESS == error);
    REQUIRE(elapsed >= 1000);
}

TEST_CASE("Test case elapsed times") {
    ReportTest ts(1000);

    int count = 5;
    for (int i=0; i<count; i++)
        ts.run(&ReportTest::test, std::to_string((long long)i));

    std::string report;
    report = ts.execute("");

    XMLDocument doc;
    doc.Parse(report.c_str());

    int elapsed_sum = 0;
    std::list<int> times;
    for (XMLElement* elem=doc.RootElement()->FirstChildElement(); elem; elem=elem->NextSiblingElement())
    {
        int elapsed = -1;
        int error = elem->QueryAttribute("elapsed", &elapsed);
        if (XML_SUCCESS == error)
        {
            elapsed_sum += elapsed;
            times.push_back(elapsed);
        }
    }

    REQUIRE(times.size() == count);
    REQUIRE(elapsed_sum >= count*(1000-2));
}


