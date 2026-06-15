#include "de_pina.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include "print_cycle.hpp"
#include "ausil_de_pina_test.hpp"
int main() {
    //prodotto_scalare
    // dimensioni diverse mi deve dare nullopt
    std::cout << "Test prodotto_scalare...\n";
    if (prodotto_scalare({true, false}, {true, false, true}).has_value()) {
        std::cerr << "ERRORE: prodotto_scalare deve restituire nullopt per dimensioni diverse\n";
        return EXIT_FAILURE;
    }
    if (prodotto_scalare({true,true,true}, {true,true,true}).value() != 1) {
        std::cerr << "ERRORE: prodotto_scalare dovrebbe essere 1\n";
        return EXIT_FAILURE;
    }
    // vettori ortogonali deve dare 0
    if (prodotto_scalare({true,false,false}, {false,true,true}).value() != 0) {
        std::cerr << "ERRORE: prodotto_scalare di vettori ortogonali dovrebbe essere 0\n";
        return EXIT_FAILURE;
    }

    //differenza_simmetrica
    // dimensioni diverse deve dare nullopt
    std::cout << "Test differenza simmetrica...\n";
    if (differenza_simmetrica({true,false}, {true,false,true}).has_value()) {
        std::cerr << "ERRORE: differenza_simmetrica dovrebbe restituire nullopt per dimensioni diverse\n";
        return EXIT_FAILURE;
    }
    // {T,F,T} XOR {F,T,T} = {T,T,F}
    auto diff = differenza_simmetrica({true,false,true}, {false,true,true});
    if (!diff.has_value() || *diff != std::vector<bool>{true,true,false}) {
        std::cerr << "ERRORE: differenza_simmetrica ha prodotto un risultato errato\n";
        return EXIT_FAILURE;
    }

    //de_pina
    // grafo vuoto, nessun ciclo
    undirected_graph<int> G_vuoto;
    std::cout << "Test de pina...\n";
    if (!de_pina(G_vuoto).empty()) {
        std::cerr << "ERRORE: de_pina su grafo vuoto dovrebbe restituire base vuota\n";
        return EXIT_FAILURE;
    }

    // albero deve darmi base vuota
    undirected_graph<int> G_albero;
    G_albero.add_edge(0,1); G_albero.add_edge(1,2); G_albero.add_edge(2,3);
    if (!de_pina(G_albero).empty()) {
        std::cerr << "ERRORE: de_pina su albero dovrebbe restituire base vuota\n";
        return EXIT_FAILURE;
    }

    // triangolo con 3 nodi e 3 archi--> 1 solo ciclo
    undirected_graph<int> G_tri;
    G_tri.add_edge(0,1); G_tri.add_edge(0,2); G_tri.add_edge(1,2);
    auto H_tri = de_pina(G_tri); //applico de pina
    print_cycle(H_tri);
    if (H_tri.size() != 1 || peso(H_tri[0]) != 3 || !is_valid_cycle(G_tri, H_tri[0])) {
        std::cerr << "ERRORE: de_pina sul triangolo ha prodotto un risultato errato\n";
        return EXIT_FAILURE;
    }

    // K4 (k=3) --> 3 cicli, tutti di peso 3
    undirected_graph<int> G_K4;
    G_K4.add_edge(0,1); G_K4.add_edge(0,2); G_K4.add_edge(0,3);
    G_K4.add_edge(1,2); G_K4.add_edge(1,3); G_K4.add_edge(2,3);
    auto H_K4 = de_pina(G_K4);
    print_cycle(H_K4);
    if (H_K4.size() != 3) {
        std::cerr << "ERRORE: de_pina su K4 dovrebbe trovare 3 cicli\n";
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < H_K4.size(); i++) {
        if (peso(H_K4[i]) != 3 || !is_valid_cycle(G_K4, H_K4[i])) {
            std::cerr << "ERRORE: il ciclo " << i << " in K4 non è valido o ha peso errato\n";
            return EXIT_FAILURE;
        }
    }
    //test esempio
    std::cout << "Esempio\n";
    undirected_graph<int> G_es;
    G_es.add_edge(1,2);
    G_es.add_edge(2,3);
    G_es.add_edge(2,4);
    G_es.add_edge(1,3);
    G_es.add_edge(4,3);
    //nell'ordine 1-2, 1-3, 2-3, 2-4, 3-4
    auto H_es = de_pina(G_es);
    print_cycle(H_es);
    if (H_es.size() != 2){
        std::cerr << "Errore: de_pina su es dovrebbe trovare 2 cicli minimi\n";
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < H_es.size(); i++){
        if (peso(H_es[i]) != 3 || !is_valid_cycle(G_es, H_es[i])){
            std::cerr << "ERRORE: il ciclo " << i << " in es non è valido o ha peso errato\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "Tutti i test superati\n";
    return EXIT_SUCCESS;
}
