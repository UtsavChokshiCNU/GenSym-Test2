#include "catch.hpp"
#include "suite.hpp"

using namespace g2::fasth;

class TestPreconditions : public g2::fasth::suite<TestPreconditions> {
public:
    TestPreconditions()
        :suite("TestPreconditions", g2::fasth::test_order::implied, g2::fasth::log_level::SILENT)
    {
    };

    void setup_test_track1()
    {
        run(&TestPreconditions::first_test, "first_test").if_success(&TestPreconditions::first_test);
    };
    void setup_test_track2()
    {
        auto& spec = run(&TestPreconditions::first_test, "first_test");
        spec.if_success(spec);
    };
    void setup_test_track3()
    {
        run(&TestPreconditions::first_test, "first_test");
        run(&TestPreconditions::second_test, "second_test").after(&TestPreconditions::first_test).if_success(&TestPreconditions::first_test);
    };
    void setup_test_track4()
    {
        auto& first = run(&TestPreconditions::first_test, "first_test");
        run(&TestPreconditions::second_test, "second_test").after(first).if_success(first);
    };
    void setup_test_track5()
    {
        run(&TestPreconditions::second_test, "second_test");
        run(&TestPreconditions::first_test, "first_test").after(&TestPreconditions::second_test).if_success(&TestPreconditions::second_test);
        run(&TestPreconditions::third_test, "third_test").after(&TestPreconditions::first_test).if_success(&TestPreconditions::first_test).if_success(&TestPreconditions::second_test);
    };
    void setup_test_track6()
    {
        run(&TestPreconditions::fourth_test, "fourth_test");
        run(&TestPreconditions::second_test, "second_test").if_success(&TestPreconditions::fourth_test);
    };

    void first_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::fail);
    }
    void second_test(const std::string& test_case_name)
    {
        complete_test_case(test_case_name, test_outcome::pass);
    }
    void third_test(const std::string& test_case_name)
    {
        static int x = 0;
        complete_test_case(test_case_name, test_outcome::pass);
        x++;
    }
    void fourth_test(const std::string& test_case_name)
    {
        tthread::this_thread::sleep_for(tthread::chrono::milliseconds(1000));
        complete_test_case(test_case_name, test_outcome::fail);
    }
};

TEST_CASE("if_success guard cannot depend on itself.") {
    TestPreconditions test_preconditions;
    REQUIRE_THROWS(test_preconditions.setup_test_track1());
}

TEST_CASE("if_success guard cannot depend on the same run.") {
    TestPreconditions test_preconditions;
    REQUIRE_THROWS(test_preconditions.setup_test_track2());
}

TEST_CASE("Second test case should fail because of if_success guard.") {
    TestPreconditions test_preconditions;
    test_preconditions.setup_test_track3();
    test_preconditions.execute();
    auto results = test_preconditions.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
    REQUIRE(results[1].outcome() == test_outcome::fail);
}

TEST_CASE("Second test run should fail because of if_success guard.") {
    TestPreconditions test_preconditions;
    test_preconditions.setup_test_track4();
    test_preconditions.execute();
    auto results = test_preconditions.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
    REQUIRE(results[1].outcome() == test_outcome::fail);
}

TEST_CASE("Testing if_success guard with multiple dependencies") {
    TestPreconditions test_preconditions;
    test_preconditions.setup_test_track5();
    test_preconditions.execute();
    auto results = test_preconditions.get_results();
    REQUIRE(results[0].outcome() == test_outcome::pass);
    REQUIRE(results[1].outcome() == test_outcome::fail);
    REQUIRE(results[1].outcome() == test_outcome::fail);
}

TEST_CASE("Testing if_success guard with delayed test case.") {
    TestPreconditions test_preconditions;
    test_preconditions.setup_test_track6();
    test_preconditions.execute();
    auto results = test_preconditions.get_results();
    REQUIRE(results[0].outcome() == test_outcome::fail);
    REQUIRE(results[1].outcome() == test_outcome::pass);
}
