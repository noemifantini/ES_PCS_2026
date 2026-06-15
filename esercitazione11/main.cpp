#include "de_pina.hpp"
#include "cicli_min_dfs.hpp"
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include <iostream>
#include "print_cycle.hpp"
int main(){
    undirected_graph<int> G;
    G.add_edge(1,2);
    G.add_edge(1,3);
    G.add_edge(2,3);
    G.add_edge(2,4);
    G.add_edge(3,4);
    auto e = G.all_edges().size();
    auto v = G.all_nodes().size();
    auto k = e - v + 1;
    //De Pina
    std::cout <<"Ricerca dei cicli minimi - De Pina...\n";
    std::vector<std::vector<int>> cicli_dp(k);
    auto cicli_bool = de_pina(G);
    std::cout <<"Bool:\n";
    print_cycle(cicli_bool);
    for (size_t i = 0; i < k; i++){
        cicli_dp[i] = bool_cycle_to_nodes(cicli_bool[i], G);
    }
    std::cout <<"Consersione:\n";
    print_cycle(cicli_dp);
    //DFS
    std::cout <<"Ricerca dei cicli minimi - DFS...\n";
    auto cicli_dfs = find_fundamental_cycles(G);
    print_cycle(cicli_dfs);
    return 0;
}
