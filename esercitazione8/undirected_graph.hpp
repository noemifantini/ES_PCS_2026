#pragma once
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <list>
class undirected_graph{
    //grafo come lista di adiacenza: nodo --> vicini map[nodi, vicini]
    std::map<int, std::set<int>> m_adj;
    
public:

    //costruttore di default
    undirected_graph(): m_adj{} {}
    //costruttore di copia
    undirected_graph(const undirected_graph& other)
        :m_adj(other.m_adj)
    {}

    //NEIGHBOUR
    std::set<int> neighbours(int n) const {
    // se il nodo non esiste, ritorna insieme vuoto
        if (m_adj.count(n) == 0)
            return {};
    // altrimenti ritorna i vicini, at poichè è const
        return m_adj.at(n);
    //map[k] aggiunge elemento se non è presente
}

    //ALL_EDGES tutti archi unici nel grafo
    std::set<undirected_edge> all_edges() const {
        std::set<undirected_edge> edges; //restituisce 
        //itera sui nodi e sui vicini
        for (const auto& [nodo, vicini]:m_adj){
            for (int nb: vicini){
                undirected_edge e(nodo, nb); //crea arco che però non è orientato
                edges.insert(e); //elimino duplicati
            }
    
        }
        return edges;

    }


    //all nodes mi dà tutti i nodi ne grafo
    std::set<int> all_nodes() const {
        std::set<int> nodi;
        //itero su mappa: 'nodo' è chiave
        for (const auto& [nodo, vicini]: m_adj){
            nodi.insert(nodo); //aggiungo
        }
        return nodi;
    }



    //add_edge() //crea arco
    void add_edge(int a, int b){
    // inserisce b tra i vicini di a e viceversa
        m_adj[a].insert(b);
        m_adj[b].insert(a);
    }



    //edge_number, mi restituisce posizione indice
    //restituisce -1 se l'arco non esiste
    int edge_number(const undirected_edge& e) const{
        //set archid dventa lista così scorro
        std::list<undirected_edge> edges(all_edges().begin(), all_edges().end());    //lista di tuti gli archi nel grafo
        int pos = 0; //inizializzazione

    //scorre la lista da inizo a fine
        for(std::list<undirected_edge>::const_iterator i = edges.begin(); i != edges.end(); ++i){
            if(*i == e)     //arco puntato è uguale a quello cercato
                return pos;
            pos++;  //incremento
        }
        return -1; // arco non presente
    }
    
    // EDGE_AT - ritorna nullopt se indice non valido
    std::optional<undirected_edge> edge_at(int idx) const {
        std::set<undirected_edge> edges = all_edges();

        if (idx < 0 || idx >= (int)edges.size())
            return std::nullopt; // niente

        int pos = 0;
        for (const auto& e : edges) {
            if (pos == idx) return e;
            pos++;
        }
        return std::nullopt; // mai raggiunto
    }


    // OPERATOR-(): archi presenti in G ma non in G'
    undirected_graph operator-(const undirected_graph& other) const {
        undirected_graph result;
        std::set<undirected_edge> edges = all_edges(); //archi del primo grafo
        std::set<undirected_edge> other_edges = other.all_edges(); //archi secondo
        //se arco non presente nel set dell'altro
        for (const auto& e : edges) {
            if (other_edges.count(e) == 0)
            //aggiungo l'arco al grafo risultato
                result.add_edge(e.from(), e.to());
        }
        return result;
    }

};