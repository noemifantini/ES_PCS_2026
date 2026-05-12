#include <iostream>
#include "undirected_edge.h"

int main() {
    undirected_edge e1(1, 2);
    undirected_edge e2(1, 3);
    undirected_edge e3(2, 1);
    undirected_edge e4(2, 3);

    // e1 e e3 sono uguali (1,2) == (2,1)
    if (e1 < e3) { std::cerr << "ERRORE e1 < e3\n"; return EXIT_FAILURE; }
    if (e3 < e1) { std::cerr << "ERRORE e3 < e1\n"; return EXIT_FAILURE; }

    // e2 non è minore di nessuno
    if (e2 < e1) { std::cerr << "ERRORE: e2 < e1\n"; return EXIT_FAILURE; }
    if (e2 < e3) { std::cerr << "ERRORE: e2 < e3\n"; return EXIT_FAILURE; }

    // e4 è il maggiore
    if (e4 < e1) { std::cerr << "ERRORE e4 < e1\n"; return EXIT_FAILURE; }
    if (e4 < e2) { std::cerr << "ERRORE e4 < e2\n"; return EXIT_FAILURE; }
    if (e4 < e3) { std::cerr << "ERRORE e4 < e3\n"; return EXIT_FAILURE; }

    std::cout << "Tutti i test superati!\n";
    return EXIT_SUCCESS;
}