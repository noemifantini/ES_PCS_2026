#include "cicli_min_dfs.hpp"
#include "print_cycle.hpp"
#include "undirected_graph.hpp"
#include <iostream>
#include "dfs_ausil.hpp"
#include <vector>
int main(){
    //test su un ciclo triangolare
    undirected_graph<int> G_t;
    G_t.add_edge(0,1);
    G_t.add_edge(1,2);
    G_t.add_edge(2,0);
    auto res_t = find_fundamental_cycles(G_t);
    auto e_t = G_t.all_edges().size();
    auto v_t = G_t.all_nodes().size();
    std::cout << "Test con grafo con " << e_t << " archi e "<< v_t << " nodi\n";
    auto exp_t = e_t - v_t + 1;
    std::cout << "Risultato atteso: " << exp_t <<" cicli\n";
    print_cycle(res_t);
    if(res_t.size() != exp_t){
        return EXIT_FAILURE;
    }
    std::set<std::set<int>> attesi_t = {{0,1,2}};
    auto ottenuti_t = converti_in_set_set(res_t);
    if (ottenuti_t != attesi_t){
        std::cerr <<"ERRORE: i nodi trovati non corrispondono a quelli attesi\n";
        return EXIT_FAILURE;
    }
    //test su un albero (aciclico)
    undirected_graph<int> G_a;
    G_a.add_edge(0,1);
    G_a.add_edge(1,2);
    G_a.add_edge(1,3);
    auto res_a = find_fundamental_cycles(G_a);
    auto e_a = G_a.all_edges().size();
    auto v_a = G_a.all_nodes().size();
    std::cout << "Test con grafo con " << e_a << " archi e "<< v_a << " nodi\n";
    auto exp_a = e_a - v_a +1;
    std::cout << "Risultato atteso: " << exp_a <<" cicli\n";
    print_cycle(res_a);
    if (res_a.size()!= exp_a){
        std::cerr << "ERRORE: trovati cicli in un albero aciclico\n";
        return EXIT_FAILURE;
    }
    //test su due cicli indipendenti (il grafo è connesso)
    undirected_graph<int> G_2;
    G_2.add_edge(0,1);
    G_2.add_edge(1,2);
    G_2.add_edge(2,0);
    G_2.add_edge(0,3); //per connettività
    G_2.add_edge(3,4);
    G_2.add_edge(5,3);
    G_2.add_edge(5,4);
    auto e_2 = G_2.all_edges().size();
    auto v_2 = G_2.all_nodes().size();
    std::cout << "Test con grafo con " << e_2 << " archi e "<< v_2 << " nodi\n";
    auto exp_2 = e_2 - v_2 +1;
    std::cout << "Risultato atteso: " << exp_2 <<" cicli\n";
    auto res_2 = find_fundamental_cycles(G_2);
    print_cycle(res_2);
    if (res_2.size() != exp_2){
        return EXIT_FAILURE;
    }
    std::set<std::set<int>> attesi_2 = {{0,1,2}, {3,4,5}};
    auto ottenuti_2 = converti_in_set_set(res_2);
    if (ottenuti_2 != attesi_2){
        std::cerr << "ERRORE: i nodi trovati non corrispondono a quelli attesi\n";
        return EXIT_FAILURE;
    }
    //test grafo vuoto
    undirected_graph<int> G_e;
    auto res_e = find_fundamental_cycles(G_e);
    auto e_e = G_e.all_edges().size();
    auto v_e = G_e.all_nodes().size();
    std::cout << "Test con grafo con " << e_e << " archi e "<< v_e << " nodi\n";
    //in un grafo vuoto non posso avere cicli fondamentali
    std::cout << "Risultato atteso: 0 cicli\n";
    print_cycle(res_e);
    if (res_e.size() != 0){
        return EXIT_FAILURE;
    }
    //esempio 4 cicli fondamentali
    undirected_graph<int> G_4;
    G_4.add_edge(1,0);
    G_4.add_edge(2,0);
    G_4.add_edge(3,0);
    G_4.add_edge(4,0);
    G_4.add_edge(1,2);
    G_4.add_edge(2,3);
    G_4.add_edge(3,4);
    G_4.add_edge(1,4);
    auto res_4 = find_fundamental_cycles(G_4);
    auto e_4 = G_4.all_edges().size();
    auto v_4 = G_4.all_nodes().size();
    std::cout << "Test con grafo con " << e_4 << " archi e "<< v_4 << " nodi\n";
    auto exp_4 = e_4 - v_4 +1;
    std::cout << "Risultato atteso: " << exp_4 <<" cicli\n";
    print_cycle(res_4);
    if (res_4.size() != exp_4){
        return EXIT_FAILURE;
    }
    
    std::cout << "Tutti i test sono stati superati con successo\n";
    return EXIT_SUCCESS;


}