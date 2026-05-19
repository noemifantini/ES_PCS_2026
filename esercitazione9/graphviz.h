#pragma once
#include <fstream>
#include <string>
#include "undirected_graph.h"

template<typename T>
void to_graphviz(const undirected_graph<T>& g, const std::string& filename) {
    std::ofstream file(filename); //apre file
    file << "graph G {" << std::endl;
    for (const auto& e : g.all_edges()) //scorre tutti gli archi e scrivo le connessioni
        file << "  " << e.from() << " -- " << e.to() << ";" << std::endl;
    file << "}" << std::endl;
}