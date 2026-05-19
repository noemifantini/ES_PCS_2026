#pragma once
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <vector>    
#include <limits>  
#include <optional>
#include "undirected_graph.h"
#include "fifolifo.hpp"

// visita del grafo: BFS se passi fifo, DFS se passi lifo
template<typename T, typename Container>
undirected_graph<T> graph_visit(const undirected_graph<T>& g, const T& start, Container c) {
    undirected_graph<T> tree;
    std::map<T, bool> reached; //mappa per nodi già visitati

    for (const T& n : g.all_nodes())
        reached[n] = false;//all'iniizo tutti i nodi sono non raggiunti

    c.put(start); //nodo di partenza nel contenitore
    reached[start] = true; //nodo partenza raggiunto 

    while (!c.empty()) {
        T u = c.get(); //esplora prossimo nodo
        for (const T& w : g.neighbours(u)) {
            if (!reached[w]) {      //se vicino non ancora raggiunto, aggiunge arco e inserisce il vicino
                reached[w] = true;
                tree.add_edge(u, w);
                c.put(w);
            }
        }
    }
    return tree;
}
// passo ricorsivo
template<typename T>
void graph_visit_recursive_step(const undirected_graph<T>& g,
                                const T& u,
                                std::map<T, bool>& reached,
                                undirected_graph<T>& tree) {
    // segno il nodo corrente come raggiunto
    reached[u] = true;

    // esploro i vicini del nodo u
    for (const T& w : g.neighbours(u)) {
        // se il vicino w non è ancora stato raggiunto
        if (!reached[w]) {
            // aggiungo l'arco all'albero
            tree.add_edge(u, w);

            // chiamata ricorsiva sul vicino
            graph_visit_recursive_step(g, w, reached, tree);
        }
    }
}

// funzione principale
template<typename T>
undirected_graph<T> graph_visit_recursive(const undirected_graph<T>& g,
                                          const T& start) {
    undirected_graph<T> tree;       // albero risultante
    std::map<T, bool> reached;      // mappa nodo se raggiunto o no

    // lancio la visita ricorsiva dal nodo start
    graph_visit_recursive_step(g, start, reached, tree);

    return tree;
}