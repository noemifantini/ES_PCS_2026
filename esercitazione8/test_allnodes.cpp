#include <cstdlib>
#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    g.add_edge(1, 2);
    g.add_edge(3, 4);

    // Dopo due archi devono esserci 4 nodi
    if (g.all_nodes().size() != 4)
        return EXIT_FAILURE;

    // Aggiungo un arco tra nodi già esistenti e il numero non cambia
    g.add_edge(1, 4);
    if (g.all_nodes().size() != 4)
        return EXIT_FAILURE;

    // Aggiungo un nuovo nodo e il numero aumenta
    g.add_edge(1, 5);
    if (g.all_nodes().size() != 5)
        return EXIT_FAILURE;
    
    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}