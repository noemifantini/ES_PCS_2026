#pragma once
#include <map>
#include <vector>    
#include <limits>  
#include <optional>
#include "undirected_graph.hpp"
#include <queue> //per priority queue

// Struttura per restituire sia distanze che predecessori
template<typename T>
struct DijkstraResult {
    std::map<T, double> dist; //mappa nodo-distanza sorg
    std::map<T, std::optional<T>> pred; //mappa nodo - predecessore
};
/* L'algoritmo Dijkstra si basa sulle code con priorità.
In C++ std::priority_queue estrae sempre il valore massimo. 
Qui sono interessata ad estrarre sempre il nodo con distanza minore;
devo, in qualche modo, invertire l'ordine */
template <typename T>
struct NodeDist{
    double dist; //distanza per raggiungere questo nodo dalla sorgente
    T node; //valore del nodo    
    bool operator> (const NodeDist& other) const{
        return dist> other.dist; //distanza minore --> priorità più alta
    }
};
template<typename T>
DijkstraResult<T> dijkstra_path(const undirected_graph<T>& g, const T& s, const T& t) {
    std::map<T, double> dist; //mappa distanze
    std::map<T, std::optional<T>> pred; //mappa predecessori
    //  INIZIALIZZAZIONE 
    for (const T& i : g.all_nodes()) {
        pred[i] = std::nullopt;                       // nessun nodo ha predecessore, funzione cppreference
        dist[i] = std::numeric_limits<double>::infinity(); // dist inziale infinto
    }

    //  SORGENTE
    if (dist.find(s) == dist.end() || dist.find(t) == dist.end()) {
        return {dist, pred}; // Nodo sorgente non trovato
    }
    dist[s] = 0.0; //distanza dalla sorgente inizializzata a 0
    //priority queue usando la struttura NodeDist
    std::priority_queue<NodeDist<T>, std::vector<NodeDist<T>>, std::greater<NodeDist<T>>> pq;
    pq.push({dist[s], s});
    
    while (!pq.empty()) {
        T u = pq.top().node; //estrazione del nodo a distanza minima
        double d = pq.top().dist; //distanza minima di questo nodo
        pq.pop(); //rimuovo dalla priority queue il nodo che ho estratto

        if (d> dist[u]){ continue;} //scartare record obsoleti
        if (dist[u] == std::numeric_limits<double>::infinity()) break; //se dist minima è inf, i ndoi sono isolati
            //guardo tutti i nodi
        if (u == t){
            break; //è ottimale --> termina la ricerca
        }
        auto neighbours_opt = g.neighbours(u);
        if (neighbours_opt){
            for (const T& w : *neighbours_opt) { 
                // grafo non pesato --> i pesi si assumono tutti pari a 1
                double new_dist = dist[u] + 1.0; 
        
            //percorso più breve di quello calcolato in precedenza
                if (dist[w] > new_dist) {
                    dist[w] = new_dist; 
                    pred[w] = u;   
                    pq.push({dist[w], w}); //aggiungo alla priority queue    
                    
                }
            }
        }
    }
    return {dist, pred};
}
/*Dal risultato ottenuto con Dijkstra non riesco ad ottenere il cammino individuato*/
template <typename T>
std::vector<T> get_shortest_path(const undirected_graph<T>& G, const T& s, const T& t){
    //costruisco con Dijkstra il Dijkstra_Path
    auto res = dijkstra_path(G, s,t);
    std::vector<T> path;
    /*Il target t potrebbe non essere raggiungibile perchè la distanza è infinito o non ho un predecessore*/
    if (res.dist[t] == std::numeric_limits<double>::infinity()){
        return path; //ritorno un vettore vuoto
    }
    /*Se il target t è raggiungibile devo ricostruire il cammino che da t mi porta alla sorgente s*/
    T curr = t; //nodo corrente
    while(!(curr == s)){ //fino a quando non raggiungo s continuo a ciclare
        path.push_back(curr);
        std::optional<T> next = res.pred[curr];
        if (!next.has_value()){
            //se il cammino si interrompesse
            return std::vector<T>();
        }
        curr = *next;
    }
    path.push_back(s);
    /*Così abbiamo costruito il vettore da t a s;
    dobbiamo inverire per avere il cammino da s a t*/
    std::reverse(path.begin(), path.end());
    return path;
}