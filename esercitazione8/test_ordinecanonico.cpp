#include <cstdlib>
#include "undirected_edge.h"
#include <iostream>

int main() {
    undirected_edge e1(1, 2);

    if (e1.from() != 1 || e1.to() != 2)
        return EXIT_FAILURE;

    // L'arco è non orientato: (2,1) deve essere normalizzato in (1,2)
    undirected_edge e2(2, 1);

    if (e2.from() != 1 || e2.to() != 2)
        return EXIT_FAILURE;

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}