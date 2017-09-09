#include "catch.hpp"
#include "test_case_graph.hpp"

TEST_CASE("Graph should detect cycle if there exists one") {
    class TestSuite;
    g2::fasth::graph<TestSuite> graph(3); // A triangle
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);
    REQUIRE(graph.is_cyclic());

    g2::fasth::graph<TestSuite> graph2(5); // http://www.alecjacobson.com/weblog/media/small-undirected-graph.png
    graph2.add_edge(0, 1);
    graph2.add_edge(1, 2);
    graph2.add_edge(1, 4);
    graph2.add_edge(2, 4);
    graph2.add_edge(1, 3);
    REQUIRE(graph.is_cyclic());
}

TEST_CASE("Graph should not detect cycle if there does not exists one") {
    class TestSuite;
    g2::fasth::graph<TestSuite> graph(3); // A linear graph
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    REQUIRE_FALSE(graph.is_cyclic());

    g2::fasth::graph<TestSuite> graph2(7); // A tree
    graph2.add_edge(0, 1);
    graph2.add_edge(1, 2);
    graph2.add_edge(2, 4);
    graph2.add_edge(1, 3);
    graph2.add_edge(3, 5);
    graph2.add_edge(3, 6);
    REQUIRE_FALSE(graph2.is_cyclic());
}