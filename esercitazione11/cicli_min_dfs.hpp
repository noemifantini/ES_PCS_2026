#pragma once
#include "graph_visit.hpp"
#include <iostream>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include <set>
#include <vector>
//NOTA: Assumiamo che i grafi siano connessi
//funzione di supporto per trovare il percorso tra u e v
template <typename T>
bool findpath(const undirected_graph<T>& G, const T& u, const T& v,
    std::vector<T>& path, std::set<T>& visited){
    visited.insert(u);
    path.push_back(u); 
    if (u==v){
        return true;
    }
    auto neighbours_opt = G.neighbours(u);
    if (neighbours_opt){
        for (const auto& n : *neighbours_opt){
            if(visited.find(n)==visited.end()){
                //se n non è già stato visitato:
                if (findpath(G, n, v, path, visited)){
                    return true;
                }
            }
        }
    }
    path.pop_back(); //non ho trovato il cammino, quindi rimuovo u dal path
    return false;
}
//Ricerca dei cicli fondamentali
template <typename T>
std::vector<std::vector<T>> find_fundamental_cycles(const undirected_graph<T>& G){
    std::vector<T> all_nodes = G.all_nodes();
    if (all_nodes.empty()){
        return {};
    }
    undirected_graph<T> dfst = recursive_dfs(G, all_nodes[0]);
    undirected_graph<T> C = G - dfst; //coalbero
    auto edges_c = C.all_edges();
    std::vector<std::vector<T>> fundamental_cycles; //vettore di vettore in cui salvare i cicli fondamentali
    for (const auto& edge: edges_c){
        //per ogni arco del coalbero calcolo il percorso tra u e v in dfst
        T u = edge.from();
        T v = edge.to();
        std::vector<T> path; //a priori non sappiamo quanto sarà lungo questo vettore
        std::set<T> visited_path; //sfruttati nella ricorsività di findpath
        if (findpath(dfst, u, v, path, visited_path)){
            path.push_back(u); //aggiungiamo u alla fine per chiudere il percorso e formare il ciclo
            fundamental_cycles.push_back(path);
        }
    }
    return fundamental_cycles;
}
