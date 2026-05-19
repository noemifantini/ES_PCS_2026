#pragma once
#include <map>
#include <vector>    
#include <limits>  
#include <optional>
#include "undirected_graph.h"

// Struttura per restituire sia distanze che predecessori
template<typename T>
struct DijkstraResult {
    std::map<T, double> dist; //mappa nodo-distanza sorg
    std::map<T, std::optional<T>> pred; //mappa nodo - predecessore
};

template<typename T>
DijkstraResult<T> dijkstra(const undirected_graph<T>& g, const T& s) {
    std::map<T, double> dist; //mappa distanze
    std::map<T, std::optional<T>> pred; //mappa predecessori
    std::vector<T> pq; //vetore coda

    //  INIZIALIZZAZIONE 
    for (const T& i : g.all_nodes()) {
        pred[i] = std::nullopt;                       // nessun nodo ha predecessore, funzione cppreference
        dist[i] = std::numeric_limits<double>::infinity(); // dist inziale infinto
    }

    //  SORGENTE
    if (dist.find(s) != dist.end()) {
        pred[s] = s;  // predecessore sorgente è se stessa
        dist[s] = 0.0; 
    } else {
        return {dist, pred}; // Nodo sorgente non trovato
    }

    // Riempiamo la PQ con tutti i nodi
    for (const T& i : g.all_nodes()) {
        pq.push_back(i); //inserisco ogni nodo del grafo nella coda
    }

    while (!pq.empty()) {
        // Dequeue: estraggo il nodo u con dist minima
        auto it_min = pq.begin();
        for (auto it = pq.begin(); it != pq.end(); ++it) {
            if (dist[*it] < dist[*it_min]) it_min = it; //trovo nodo con dist minima
        }

        T u = *it_min;
        pq.erase(it_min); //rimuovo nodo dalla coda

        if (dist[u] == std::numeric_limits<double>::infinity()) break; //se dist minima è inf, i ndoi sono isolati
            //guardo tutti i nodi
        for (const T& w : g.neighbours(u)) {
            // non ci sono pesi
            double new_dist = dist[u] + 1.0; 

        //percorso più breve di quello calcolato in precedenza
            if (dist[w] > new_dist) {
                dist[w] = new_dist; 
                pred[w] = u;       
                
            }
        }
    }

    return {dist, pred};
}