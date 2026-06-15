#include "ausil_de_pina_test.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
int main(){
    /*per peso i test sono quasi "superflui" in quanto si tratta della semplice 
    applicazione di std::count sui vettori di bool; per completezza ne effettuiamo un paio*/
    std::vector<bool> v1(5);
    v1 = {true, true, false, false, true};
    auto p1 = peso(v1);
    if (p1 != 3){
        std::cerr << "ERRORE nella funzione peso\n";
        return EXIT_FAILURE;
    }
    std::vector<bool> v2(3);
    v2 = {false, false, false};
    auto p2 = peso(v2);
    if (p2 != 0){
        std::cerr << "ERRORE nella funzione peso\n";
        return EXIT_FAILURE;
    }
    std::cout << "I test sulla funzione peso sono stati superati con successo\n";
    //test sulla funzione is_valid_cycle
    //test grafo con un numero di archi diverso dal numero di cicli
    undirected_graph<int> G1;
    G1.add_edge(1,2);
    G1.add_edge(2,1);
    G1.add_edge(1,3); //grafo con 3 archi
    std::vector<bool> C1(2);
    C1 = {true, true};
    if (is_valid_cycle(G1,C1)){
        std::cerr << "ERRORE: il numero di archi in C1 è diverso dalla dimensione di C1, ma is_valid_cycle restituisce true\n";
        return EXIT_FAILURE;
    }
    //ciclo valido
    undirected_graph<int> G2;
    G2.add_edge(0, 1); // Indice 0
    G2.add_edge(1, 2); // Indice 1
    G2.add_edge(2, 0); // Indice 2
    std::vector<bool> C2_valido = {true, true, true};
    bool result2 = is_valid_cycle(G2, C2_valido);
    if (!result2){
        std::cerr << "ERRORE: un ciclo valido non viene riconosciuto come tale\n";
        return EXIT_FAILURE;
    }
    /*modifico C2 rimuovendo l'arco (2,0); 
    in questo caso, i nodi 0 e 1 hanno grado 1 --> fallimento di is_valid_cycle*/
    std::vector<bool> C2_non_valido = {true, true, false};
    bool result2_no = is_valid_cycle(G2, C2_non_valido);
    if (result2_no){
        std::cerr << "ERRORE: un ciclo non valido (nodi dispari) viene riconosciuto vome valido\n";
        return EXIT_FAILURE;
    }
    //nodo 0 con grado 3
    undirected_graph<int> G3;
    G3.add_edge(0, 1); 
    G3.add_edge(0, 2); 
    G3.add_edge(0, 3); 
    std::vector<bool> C_3 = {true, true, true};
    bool result3 = is_valid_cycle(G3, C_3);
    if (result3){
        std::cerr << "ERRORE: un ciclo non valido (nodi dispari) viene riconosciuto vome valido\n";
        return EXIT_FAILURE;
    }
    std::cout << "Tutti i test sono stati superati con successo\n";
    return EXIT_SUCCESS;
}