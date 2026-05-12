#include <iostream>
#include "undirected_edge.h"
int main(){
    undirected_edge e1(1,3);
    undirected_edge e2 (1,5);
    undirected_edge e3(3,1);
    if (e1 != e3){
        return EXIT_FAILURE;
    }
    if (!(e1 != e2)){
        return EXIT_FAILURE;
    }

    std::cout << "tutti i test passati" << std::endl;
    return EXIT_SUCCESS;
}