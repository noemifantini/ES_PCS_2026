#pragma once
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <optional> 
#include "undirected_edge.h"

template <typename T>
class undirected_graph {
    // grafo come lista di adiacenza: nodo --> vicini
    // Usiamo T come tipo per i nodi
    std::map<T, std::set<T>> m_adj;
    
public:
    // costruttore di default
    undirected_graph() : m_adj{} {}

    // costruttore di copia
    undirected_graph(const undirected_graph& other)
        : m_adj(other.m_adj)
    {}

    // NEIGHBOUR
    // n è di tipo T (passato per riferimento costante per efficienza)
    std::set<T> neighbours(const T& n) const {
        // se il nodo non esiste, ritorna insieme vuoto
        if (m_adj.count(n) == 0)
            return {};
        // altrimenti ritorna i vicini, at poiché è const
        return m_adj.at(n);
    }

    // ALL_EDGES tutti archi unici nel grafo
    std::set<undirected_edge<T>> all_edges() const {
        std::set<undirected_edge<T>> edges; 
        // itera sui nodi e sui vicini
        for (const auto& [nodo, vicini] : m_adj) {
            for (const T& nb : vicini) {
                undirected_edge<T> e(nodo, nb); // crea arco usando T
                edges.insert(e); // elimino duplicati grazie all'operatore < di edge
            }
        }
        return edges;
    }

    // all nodes mi dà tutti i nodi nel grafo
    std::set<T> all_nodes() const {
        std::set<T> nodi;
        // itero su mappa: 'nodo' è chiave
        for (const auto& [nodo, vicini] : m_adj) {
            nodi.insert(nodo); 
        }
        return nodi;
    }

    // add_edge() // crea arco tra due nodi di tipo T
    void add_edge(const T& a, const T& b) {
        // inserisce b tra i vicini di a e viceversa
        m_adj[a].insert(b);
        m_adj[b].insert(a);
    }

    // edge_number, mi restituisce posizione indice
    // restituisce -1 se l'arco non esiste
    int edge_number(const undirected_edge<T>& e) const {
        // creiamo la lista basandoci sugli archi di tipo T
        std::list<undirected_edge<T>> edges(all_edges().begin(), all_edges().end());
        int pos = 0; 

        // scorre la lista usando l'iteratore della lista templatizzata
        for (typename std::list<undirected_edge<T>>::const_iterator i = edges.begin(); i != edges.end(); ++i) {
            if (*i == e) 
                return pos;
            pos++; 
        }
        return -1; 
    }

    // EDGE_AT: ritorna nullopt se indice non valido
    std::optional<undirected_edge<T>> edge_at(int idx) const {
        std::set<undirected_edge<T>> edges = all_edges();

        if (idx < 0 || idx >= (int)edges.size())
            return std::nullopt;

        int pos = 0;
        for (const auto& e : edges) {
            if (pos == idx) return e;
            pos++;
        }
        return std::nullopt;
    }

    // OPERATOR-(): archi presenti in G ma non in G'
    undirected_graph<T> operator-(const undirected_graph<T>& other) const {
        undirected_graph<T> result;
        std::set<undirected_edge<T>> edges = all_edges();
        std::set<undirected_edge<T>> other_edges = other.all_edges();
        
        for (const auto& e : edges) {
            if (other_edges.count(e) == 0)
                result.add_edge(e.from(), e.to());
        }
        return result;
    }
};