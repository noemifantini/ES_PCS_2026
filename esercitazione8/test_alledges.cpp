#include <cstdlib>
#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    // Grafo vuoto: nessun arco
    if (g.all_edges().size() != 0){
        std::cerr << "FALLITO: grafo vuoto" << std::endl;
        return EXIT_FAILURE;
    }
    // Aggiunta di 3 archi
    g.add_edge(1, 2);
    g.add_edge(5, 6);
    g.add_edge(4, 3);

    if (g.all_edges().size() != 3)

        return EXIT_FAILURE;

    // Arco duplicato: non deve aumentare la size
    g.add_edge(6, 5);

    if (g.all_edges().size() != 3)
        return EXIT_FAILURE;

    auto edges = g.all_edges();

    // Controllo presenza archi
    if (edges.count(undirected_edge(1,2)) != 1)
        return EXIT_FAILURE;

    if (edges.count(undirected_edge(6,5)) != 1)
        return EXIT_FAILURE;

    if (edges.count(undirected_edge(10,8)) != 0)
        return EXIT_FAILURE;

    // Controllo ordine degli archi
    auto it = edges.begin();

    if (*it != undirected_edge(1,2)) return EXIT_FAILURE;
    ++it;

    if (*it != undirected_edge(3,4)) return EXIT_FAILURE;
    ++it;

    if (*it != undirected_edge(5,6)) return EXIT_FAILURE;

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}