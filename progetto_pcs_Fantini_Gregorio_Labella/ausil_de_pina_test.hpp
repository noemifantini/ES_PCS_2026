#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <map>
//funzioni ausiliarie per i test di De Pina
//conto il numero di archi nel ciclo
int peso(const std::vector<bool>& v) {
    return std::count(v.begin(), v.end(), true);
}

//servirà per verificare nei test su de_pina che ogni nodo sia di grado 0 o 2
bool is_valid_cycle(const undirected_graph<int>& G, const std::vector<bool>& C) {
    auto edges = G.all_edges();
    auto nodes = G.all_nodes();
    if (C.size() != edges.size()) return false; //vettore tanti elementi quanti sono gli archi
    std::map<int, int> degree;
    for (const auto& n : nodes) degree[n] = 0; //inizializzo gradi a zero
    for (size_t i = 0; i < edges.size(); i++)
        if (C[i]) { degree[edges[i].from()]++; degree[edges[i].to()]++; }
    for (const auto& [node, deg] : degree)
        if (deg != 0 && deg != 2) return false;
    return true;
}
