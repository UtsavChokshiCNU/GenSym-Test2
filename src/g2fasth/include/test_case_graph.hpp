#pragma once
#ifndef INC_LIBG2FASTH_TEST_CASE_GRAPH_H
#define INC_LIBG2FASTH_TEST_CASE_GRAPH_H

#include <list>
#include "g2fasth_enums.hpp"

class test_run_spec;

namespace g2 {
namespace fasth {
template <class T>
/**
* This class is used to create graph of test case for cycle detections.
*/
class graph
{
public:
    /**
    * Constructor, that takes number of vertices as parameter.
    */
    graph(int vertices)
        : d_vertices(vertices)
        , adjacency_list(vertices)
    {
    }
    /**
    * This function adds an edge in adjacency list.
    */
    void add_edge(int dependent, int dependency) {
        adjacency_list[dependent].push_back(dependency);
        adjacency_list[dependency].push_back(dependent);
    }
    /**
    * This function is responsible for detecting cycle in adjacency list.
    */
    bool is_cyclic() {
        std::vector<bool> visited(d_vertices);
        visited.assign(d_vertices, false);
        for (int i = 0; i < d_vertices; i++)
        {
            if (!visited[i] && is_cyclic(i, visited, -1))
            {
                return true;
            }
        }
        return false;
    }
private:
    int d_vertices;
    std::vector<std::vector<int>> adjacency_list;
    bool is_cyclic(int start_index, std::vector<bool> visited, int parent) {
        visited.at(start_index) = true;
        for (auto i = adjacency_list[start_index].begin(); i != adjacency_list[start_index].end(); ++i)
        {
            if (!visited[*i])
            {
                if (is_cyclic(*i, visited, start_index))
                {
                    return true;
                }
            }
            else if (*i != parent)
            {
                return true;
            }
        }
        return false;
    }
};
}
}

#endif // !INC_LIBG2FASTH_TEST_CASE_GRAPH_H