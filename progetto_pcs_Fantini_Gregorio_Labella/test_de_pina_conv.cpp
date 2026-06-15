#include <iostream>
#include <vector>
#include <set>
#include "undirected_edge.hpp"
#include "de_pina.hpp"
#include "undirected_graph.hpp"
int main(){
    undirected_graph<int> G;
    G.add_edge(1, 2); // Arco 0
    G.add_edge(2, 3); //2
    G.add_edge(1, 3); //1
    G.add_edge(3, 4); //3
    G.add_edge(4, 5); //5
    G.add_edge(5, 6); //6
    G.add_edge(3, 6); //4
    G.add_edge(6, 7); //7
    auto all_e = G.all_edges();
    size_t n_archi = all_e.size();
    //test conversione ciclo vuoto
    std::vector<bool> ciclo_v(n_archi, false);
    auto ris_v = bool_cycle_to_nodes(ciclo_v, G);
    if(!ris_v.empty()){
        std::cerr <<"ERRORE: da un ciclo bool vuoto si è ottenuto non vuoto\n";
        return EXIT_FAILURE;
    }
    //ciclo triangolare  (1,2,3)
    std::vector<bool> ciclo_t(n_archi, false);
    ciclo_t[1] = true;
    ciclo_t[2] = true;
    ciclo_t[0] = true;
    auto res_t = bool_cycle_to_nodes(ciclo_t, G);
    if(res_t.size() != 4){
        std::cerr <<"ERRORE: il triangolo deve produrre una sequenza di 4 nodi\n";
        return EXIT_FAILURE;
    }
    if(res_t.front()!= res_t.back()){
        std::cerr <<"ERRORE: il ciclo non si è chiuso correttamente\n";
        return EXIT_FAILURE;
    }
    //costruiamo il set nodi ottenuti e il set dei nodi attesi
    std::set<int> nodi_attesi_t = {1,2,3};
    std::set<int> nodi_ottenuti_t(res_t.begin(), res_t.end());
    if (nodi_attesi_t != nodi_ottenuti_t){
        std::cerr <<"ERRORE: i nodi estratti non corrispondono ai nodi attesi\n";
        return EXIT_FAILURE;
    }
    //test su quadrilatero (3,4,5,6)
    std::vector<bool> ciclo_q(n_archi, false);
    ciclo_q[3] = true;
    ciclo_q[5] = true;
    ciclo_q[6] = true;
    ciclo_q[4] = true;
    auto res_q = bool_cycle_to_nodes(ciclo_q, G);
    if(res_q.size() != 5){
        std::cerr <<"ERRORE: il quadrilatero deve produrre una sequenza di 5 nodi\n";
        return EXIT_FAILURE;
    }
    if(res_q.front()!= res_q.back()){
        std::cerr <<"ERRORE: il ciclo non si è chiuso correttamente\n";
        return EXIT_FAILURE;
    }
    //costruiamo il set nodi ottenuti e il set dei nodi attesi
    std::set<int> nodi_attesi_q = {3,4,5,6};
    std::set<int> nodi_ottenuti_q(res_q.begin(), res_q.end());
    if (nodi_attesi_q != nodi_ottenuti_q){
        std::cerr <<"ERRORE: i nodi estratti non corrispondono ai nodi attesi\n";
        return EXIT_FAILURE;
    }
    //caso degenere: cammino aperto
    std::vector<bool> ciclo_ap(n_archi, false);
    //attiviamo archi (1,2), (2,3)
    ciclo_ap[0] = true;
    ciclo_ap[2] = true;
    auto res_ap = bool_cycle_to_nodes(ciclo_ap, G);
    if (!res_ap.empty()){
        std::cerr<<"ERRORE: ciclo aperto dovrebbe restituire un vuoto\n";
        return EXIT_FAILURE;
    }
    std::cout <<"Tutti i test sono stati superati con successo\n";
    return EXIT_SUCCESS;
}