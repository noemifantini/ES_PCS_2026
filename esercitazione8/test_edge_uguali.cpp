#include <cstdlib>
#include "undirected_edge.h"
#include <iostream>

int main() {
    undirected_edge e1(1, 3);
    undirected_edge e2(1, 4);
    undirected_edge e3(3, 1);

    // e1 e e3 devono essere uguali
    if (!(e1 == e3))
        return EXIT_FAILURE;

    // e1 e e2 devono essere diversi
    if (e1 == e2)
        return EXIT_FAILURE;

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}