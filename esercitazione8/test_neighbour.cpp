#include <cstdlib>
#include "undirected_edge.h"
#include <iostream>
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    g.add_edge(1, 1);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 3);

    // Neighbors del nodo 1
    auto nb1 = g.neighbours(1);
    if (nb1.size() != 3 ||
        nb1.count(1) != 1 ||
        nb1.count(2) != 0 ||
        nb1.count(3) != 1 ||
        nb1.count(4) != 1)
        return EXIT_FAILURE;

    // Neighbors del nodo 3
    auto nb3 = g.neighbours(3);
    if (nb3.size() != 2 ||
        nb3.count(1) != 1 ||
        nb3.count(2) != 1)
        return EXIT_FAILURE;

    // Nodo inesistente: deve restituire insieme vuoto
    if (!g.neighbours(5).empty())
        return EXIT_FAILURE;

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}