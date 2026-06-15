#pragma once
#include <iostream>
#include <vector>
//Costruzione di una funzione che permetta di stampare i cicli e l'output di De Pina
template <typename T>
void print_cycle(const std::vector<std::vector<T>>& cycles){
    /*i cicli sono memorizzati come vettori e, quelli restituiti da find_fundamental_cycles
    sono raccolti a propria volta in un vettore per una rappresentazione compatta in memoria e per 
    un accesso in tempo costante agli elementi*/
    if (cycles.empty()){
        //non sono stati trovati cicli fondamentali
        std::cout << "Nessun ciclo trovato.\n";
        return;
    }
    for (size_t i = 0; i < cycles.size(); ++i){
        std::cout << "Ciclo n. "<< i+1 <<":\n";
        for (const auto& node : cycles[i]){
            std::cout << node << " "; 
            /*i nodi sono assunti essere di tipo intero, quindi è un separatore "robusto"*/
        }
        std::cout << "\n";
    }
}
