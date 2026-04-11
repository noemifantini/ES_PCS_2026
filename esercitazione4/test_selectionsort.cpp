#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <random>
#include "sorts.hpp"
#include "randfiller.h"

int main(){
    randfiller generato;
    for (int t = 0; t<100;t++){     //100 vettori di prova
        int dimensione = rand() % 101;      //dimensione scelta a caso
        std::vector<int> v(dimensione);
        
        generato.fill(v,-100,100);
        selection_sort(v);

        if (!is_sorted(v)){     //verificare che il vettore sia ordinato
            std::cerr << "ERRORE: Test fallito";
            return EXIT_FAILURE;
        }
    }
    std::cout << "SUCCESSO: Test corretto";
    return EXIT_SUCCESS;

}