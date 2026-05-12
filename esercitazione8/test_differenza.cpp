#include <cstdlib>
#include <iostream>
#include "undirected_graph.h"

void test_diff_size() {
    undirected_graph G, G2;
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G2.add_edge(1, 2);
    if ((G - G2).all_edges().size() != 1)
        exit(EXIT_FAILURE);
}

void test_diff_arco_rimasto() {
    undirected_graph G, G2;
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    G2.add_edge(1, 2);
    if ((G - G2).all_edges().count(undirected_edge(0,1)) != 1) exit(EXIT_FAILURE);
}

void test_diff_se_stessi() {
    undirected_graph G;
    G.add_edge(0, 1);
    G.add_edge(1, 2);
    if (!(G - G).all_edges().empty()) exit(EXIT_FAILURE);
}

int main() {
    test_diff_size();
    test_diff_arco_rimasto();
    test_diff_se_stessi();
    return 0;
}



