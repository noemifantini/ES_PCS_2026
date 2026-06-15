#pragma once
#include <map>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "fifo.hpp"
#include "lifo.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
/*se s (stack) --> visita in profondità; 
se q (queue) --> visita in ampiezza*/
//visit graph
template <typename T, typename Container>
//Container --> fifo o lifo che stabilisce l'ordine di visita
undirected_graph<T> graph_visit(const undirected_graph<T>& g, const T& v, Container c){
    undirected_graph<T> tree;
    //mi baso sugli appunti presi a lezione
    //creo una map per vedere se ho già visitato i nodi
    std::map<T, bool> reached;
    //inizializzo i nodi come non raggiunti
    for (const auto&n : g.all_nodes()){
        reached[n] = false;
    }
    /*se la sorgente (v) esiste, la inserisco nel container
    + segno che è stata visitata*/
    if(reached.find(v) != reached.end()){
        c.put(v);
        reached[v] = true;
        /*per ora la sorgente è un nodo (radice) isolato;
        non l'aggiungo ancora all'albero perchè non posso aggiungere nodi
        isolati (si veda undirected_graph.h)*/ 
    }
    while (!c.empty()){
        auto u_opt = c.get();  //procedo ad estrarre il nodo corrente; alla prima iterazione è v
        if (! u_opt){
	        continue;
	    }
	    auto u = *u_opt; //estraggo il nodo corrente; alla prima iterazione è v        
	    auto vicini_opt = g.neighbours(u);
        if (vicini_opt){
            for (const auto&w : *vicini_opt){
                if (!reached[w]){
                    reached[w] = true;
                    c.put(w);
                    //creo l'arco nell'albero
                    tree.add_edge(u,w);
                }
            }
        }
    }
    return tree;
}
//recursive dfs
template <typename T>
void dfs_recursive_step(const undirected_graph<T>& g, const T& u, std::map<T, bool>& reached, undirected_graph<T>& tree){
    //per prima cosa salvo il nodo u come visitato
    reached[u] = true;
    //ottengo i vicini del nodo
    auto vicini_opt = g.neighbours(u);
    if (vicini_opt){
	    /*nota sull'ordine di visita: esploro i vicini nell'ordine in cui sono memorizzati nel grafo;
	    una dfs iterativa ha ordine di estrazione inverso all'ordine di inserimento (policy LIFO dello stack);
	    dal punto di vista logico, anche questo algoritmo è valido*/
        for (const T& v: *vicini_opt){
            if(!reached[v]){
                //aggiungo all'albero
                tree.add_edge(u,v);
                //voglio scendere in profondità --> chiamata ricorsiva
                dfs_recursive_step(g, v, reached, tree); 
                
            }
        }
    }
    return;
}
template <typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& g, const T& v){
    undirected_graph<T> tree;
    std::map<T, bool> reached;
    //inizializzo tutti i nodi come non visitati
    for (const auto& n : g.all_nodes()){
        reached[n] = false;
    }
    //il nodo sorgente esiste nel grafo? Se sì, avvio la ricerca
    if(reached.find(v) != reached.end()){
        //avvio la ricorsione
        dfs_recursive_step(g, v, reached, tree);
    }
    return tree;
}
/*per poter realizzare i grafi con GraphViz, mi serve un file .dot*/
template <typename T>
void write_dot(const std::string& f_name, const undirected_graph<T>& g, const std::string& g_label){
    std::ofstream f(f_name);
    f << "graph G {\n";
    if (!g_label.empty()){
        f << " label = "<< g_label <<";\n";
    }
    for (const auto& n: g.all_nodes()){
        f << " " <<n <<" ;\n";
    }
    for (const auto& e : g.all_edges()){
        f << " " << e.from()<< " -- "<< e.to() <<" ;\n";
    }
    f << "}\n";
}


