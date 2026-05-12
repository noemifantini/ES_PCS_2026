#include <cstdlib>
#include <iostream>
#include "undirected_graph.h"

void test_edge_number_presente() {
    undirected_graph G;
    G.add_edge(0, 1);
    if (G.edge_number(undirected_edge(0,1)) != 0) exit(EXIT_FAILURE);
}

void test_edge_number_assente() {
    undirected_graph G;
    if (G.edge_number(undirected_edge(5,6)) != -1) exit(EXIT_FAILURE);
}

int main() {
    test_edge_number_presente();
    test_edge_number_assente();
    return 0;
}
