#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <optional>
#include "undirected_edge.hpp"
template <typename T>
class undirected_graph{
    /*creo la lista di adiacenza utilizzando un vettore di vettori;
    esso permette di operare la gestione dei vicini in tempo lineare 
    (preferibile al tempo logaritmico se si lavora con grafi di PICCOLE dimensioni).
    Si tratta, inoltre, di una rappresentazione molto compatta in memoria*/
    /*lista di adiacenza: {nodo, vic1, vic2, ...}*/
    std::vector<std::vector<T>> m_adj;
    /*definisco degli operatori privati che torneranno utili in seguito*/
    /*definisco un comparatore che confronta una riga con un valore.
    Tornerò utile per std::lower_bound*/
    
    static bool comparator(const std::vector<T>& riga, const T& val){
        return riga[0]<val;
    }
    //trova o inserisce la riga del nodo + restituzione indice
    //avviene privatamente
    std::size_t find_or_insert(const T& nodo){
        auto it = std::lower_bound(m_adj.begin(), m_adj.end(), nodo, comparator);
        if (it == m_adj.end() || (*it)[0] != nodo){
            std::size_t idx = it - m_adj.begin();
            m_adj.insert(it, std::vector<T>{nodo}); //inserisco la riga {nodo}
            return idx;
        }
        return it - m_adj.begin(); //ritorno all'indice se il nodo esiste già
    }
    //trovo l'indice di un nodo
    std::size_t row_of(const T& nodo) const{
        auto it = std::lower_bound(m_adj.begin(), m_adj.end(), nodo, comparator);
        if (it != m_adj.end() && (*it)[0] == nodo){
            return static_cast<std::size_t>(it - m_adj.begin());
        }
        return m_adj.size();
    }
    public:
        //costruttore di default
        undirected_graph() {};
        //costruttore di copia
        undirected_graph(const undirected_graph<T>& g)
            :m_adj(g.m_adj) 
        {}
        //operatore di assegnazione per copia
        undirected_graph& operator= (const undirected_graph<T>& g){
            //vado a sovrascrivere un oggetto già esistente per creare una copia di g
            if (this != &g){
                m_adj = g.m_adj;
            }
            return *this;
        }
        /*aggiungo un arco al grafo; se i nodi non esistono, li creo tramite
        find_or_insert*/ 
        void add_edge (const T& u, const T& v){
            undirected_edge<T> e(u,v);
            T from = e.from();
            T to = e.to();
            std::size_t idx_from = find_or_insert(from);
            std::size_t idx_to = find_or_insert(to);
            //ai vicini di from bisogna aggiungere to, se non c'è già
            auto& neighbours_from = m_adj[idx_from]; //creo un riferimento all'elemento senza copiarlo
            //se usassi la funzione neighbours definita in seguito avrei una copia
            //qui devo modificare --> riferimento
    		auto it_to = std::lower_bound(neighbours_from.begin()+1, neighbours_from.end(), to);
    		if (it_to == neighbours_from.end() || *it_to != to){
        		neighbours_from.insert(it_to, to); //to non c'è ancora, quindi lo inserisco
    		}
            //ai vicini di to bisogna aggiungere from, se non c'è già
            auto& neighbours_to = m_adj[idx_to];
            auto it_from = std::lower_bound(neighbours_to.begin()+1, neighbours_to.end(),from);
            if (it_from != neighbours_to.end() || *it_from != from){
	            //from non c'è ancora, lo inserisco alla posizione individuata
	            neighbours_to.insert(it_from, from);
	            }
        }
        //neighbours
        std::optional<std::vector<T>> neighbours(const T& nodo) const {
            std::size_t idx = row_of(nodo);
            if (idx >= m_adj.size()){
                return std::nullopt;
            }
            return std::vector<T>(m_adj[idx].begin()+1, m_adj[idx].end());
        }
        //all_adges
        std::vector<undirected_edge<T>> all_edges() const{
            std::vector<undirected_edge<T>> edges;
            //ciclo sulle righe
            for (const auto& riga:m_adj){
                T u = riga[0]; //primo elemento (nodo)
                //per ogni riga devo prendere gli elementi dal primo in poi
                for (std::size_t i = 1; i < riga.size(); ++i){
                    //grafo non diretto --> aggiungo ogni arco una sola volta
                    T v = riga[i];
                    //usare std::find sul vettore per vedere se c'è ha costo O(n^2)
                    //usare if permette di ridurre costo
                    if (u<=v){
                        /*il <= serve per gestire i cappi*/
                        edges.push_back(undirected_edge<T> (u,v));
                    }
                }
            }
            /*quando faccio add_edge --> ordinamento dei vicini;
            Quando visito gli archi, poichè i vicini sono memorizzati in un vettore, conservo l'ordinamento
            --> non serve std::sort*/
            return edges;
        }
        //all_nodes
        std::vector<T> all_nodes() const {
            //devo prendere il primo vettore di ogni riga
            std::vector<T> nodi;
            for (const auto& riga: m_adj){
                nodi.push_back(riga[0]);
            }
            return nodi;
        }
        //edge_number
        //qui optional
        std::optional<std::size_t> edge_number(const undirected_edge<T>& e) const{
            auto edges = all_edges(); //vettore ordinato
            //std::lower_bound per iteratore al primo elemento >= e
            auto it = std::lower_bound(edges.begin(), edges.end(),e);
            //verifico di aver trovato l'elemento cercato
            if (it!= edges.end() && *it ==e){
                //static_cast converte il risultato di questa differenza in un tipo size_t (come iteratore)
                return static_cast<std::size_t>(it-edges.begin());
            }
            return std::nullopt;
        }
        //edge_at 
        //optional
        std::optional<undirected_edge<T>> edge_at(std::size_t idx) const {
            auto edges = all_edges();
            //se out_of_range
            if (idx>= edges.size()){
                return std::nullopt;
            }
            return edges[idx];
        }
        //differenza
        undirected_graph<T> operator-(const undirected_graph<T>& g) const {
            undirected_graph<T> r;
            auto my_e = all_edges();
            auto g_e = g.all_edges();
            for (const auto&e : my_e){
                //lower_bound per trovare dove e potrebbe trovarsi in g_e
                auto it = std::lower_bound(g_e.begin(), g_e.end(), e);
                //se iteratore alla fine o non trovo e --> arco non presente nel secondo grafo
                if (it == g_e.end()|| *it!=e){
                    r.add_edge(e.from(), e.to());
                }
            }
            return r;
        }
};