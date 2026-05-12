#include <cstdlib>
#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"

int main() {
    undirected_graph g;

    g.add_edge(1, 2);
    g.add_edge(2, 3);

    // Controllo nodi
    if (g.all_nodes().size() != 3){
        std::cerr << "errore nodi" << std::endl;
        return EXIT_FAILURE;
    }

    // Controllo che gli archi siano 2
    if (g.all_edges().size() != 2) {
        std::cerr << "errore archi" << std::endl;
        return EXIT_FAILURE;
    }
    // Test duplicato: non deve aumentare il numero di archi
    g.add_edge(2, 1);

    if (g.all_edges().size() != 2){
        std::cerr << "errore duplicati" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}