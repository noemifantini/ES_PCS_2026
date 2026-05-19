#include <iostream>
#include "undirected_edge.h"
#include "undirected_graph.h"
#include "grafi_visita.hpp"
#include "graphviz.h"
#include "fifolifo.hpp"
#include "dikistra.hpp"

int main() {
    // Costruisco il grafo originale
    undirected_graph<int> g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 4);
    g.add_edge(4, 5);

    // BFS con fifo
    std::cout << "\nBFS" << std::endl;
    fifo<int> q; 
    auto bfs = graph_visit(g, 1, q);
    to_graphviz(bfs, "bfs.dot"); 
    std::cout << "Generato bfs.dot" << std::endl;

    // DFS iterativa con lifo
    std::cout << "\nDFS iterativa" << std::endl;
    lifo<int> s;
    auto dfs = graph_visit(g, 1, s);
    to_graphviz(dfs, "dfs.dot");
    std::cout << "Generato dfs.dot" << std::endl;

    // DFS ricorsiva
    std::cout << "\nDFS ricorsiva-" << std::endl;
    auto rdfs = graph_visit_recursive(g, 1); 
    to_graphviz(rdfs, "rdfs.dot");
    std::cout << "Generato rdfs.dot" << std::endl;

    // Dijkstra e generazione albero dei cammini minimi
    std::cout << "\nDijkstra" << std::endl;
    auto result = dijkstra(g, 1);

    undirected_graph<int> dijkstra_tree;
    for (const auto& [nodo, pred] : result.pred) {
        if (pred.has_value() && pred.value() != nodo) {
            dijkstra_tree.add_edge(pred.value(), nodo);
        }
    }
    to_graphviz(dijkstra_tree, "dijkstra.dot");
    std::cout << "Generato dijkstra.dot" << std::endl;

    return 0;
}