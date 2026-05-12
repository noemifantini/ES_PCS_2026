#include <cstdlib>
#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.add_edge(5, 6);

    // Test edge_at su indici         //funzione trovata su cppreference
    if (!g.edge_at(0).has_value() || g.edge_at(0).value() != undirected_edge(1,2)) {
        std::cerr << "FALLITO" << std::endl;
        return EXIT_FAILURE;
    }
    if (!g.edge_at(1).has_value() || g.edge_at(1).value() != undirected_edge(3,4)) {
        std::cerr << "FALLITO" << std::endl;
        return EXIT_FAILURE;
    }
    if (!g.edge_at(2).has_value() || g.edge_at(2).value() != undirected_edge(5,6)) {
        std::cerr << "FALLITO" << std::endl;
        return EXIT_FAILURE;
    }

    // Test indici non validi (devono restituire nullopt)
    if (g.edge_at(10).has_value()) {
        std::cerr << "FALLITO" << std::endl;
        return EXIT_FAILURE;
    }
    if (g.edge_at(-5).has_value()) {
        std::cerr << "FALLITO" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}