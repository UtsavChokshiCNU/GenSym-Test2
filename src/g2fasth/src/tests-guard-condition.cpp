#include "catch.hpp"
#include "suite.hpp"
#include "g2fasth_enums.hpp"
#include "test_run_spec.hpp"

class TestGuard : public g2::fasth::suite<TestGuard> {
public:
    TestGuard(bool bParam)
        :suite("TestGuard", g2::fasth::test_order::implied, g2::fasth::log_level::SILENT)
        , d_bParam(bParam)
        , firstCalled(false) {
    };
    void setup_test_track() override
    {
        run(&TestGuard::first_test, "third_test_again").guard([this] { return this->d_bParam == true; });
    };
    g2::fasth::test_outcome first_test()
    {
        firstCalled = true;
        return g2::fasth::test_outcome::pass;
    }
    bool firstCalled;
    bool d_bParam;
};

TEST_CASE("Test case should not be executed if guard condition fails.") {
    TestGuard test_guard(false);
    test_guard.execute();
    REQUIRE_FALSE(test_guard.firstCalled);
}

TEST_CASE("Test case should be executed if guard condition passes.") {
    TestGuard test_guard(true);
    test_guard.execute();
    REQUIRE(test_guard.firstCalled);
}