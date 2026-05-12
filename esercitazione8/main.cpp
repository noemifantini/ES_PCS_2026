#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    // aggiungo archi
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    // stampo nodi
    std::cout << "Nodi: ";
    for (int n : g.all_nodes())
        std::cout << n << " ";
    std::cout << std::endl;

    // stampo archi
    std::cout << "Archi: ";
    for (const auto& e : g.all_edges())
        std::cout << e << " ";
    std::cout << std::endl;

    // stampo vicini di 2
    std::cout << "Vicini di 2: ";
    for (int n : g.neighbours(2))
        std::cout << n << " ";
    std::cout << std::endl;

    // edge_number
    std::cout << "Indice arco (1,2): " << g.edge_number(undirected_edge(1,2)) << std::endl;

    // edge_at
    auto e = g.edge_at(0);
    if (e.has_value())
        std::cout << "Arco all'indice 0: " << e.value() << std::endl;

    return 0;
}