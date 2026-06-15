#pragma once
#include "graph_visit.hpp"
#include <iostream>
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include <set>
#include <vector>
#include <map>
#include "dijkstra_path.hpp"


/*Algoritmo implementato assumendo di lavorare con grafi generici,al fine di consegnarlo
come esercitazione 11. Per questo, non si sfrutta l'attributo indici della struttura circuito*/
//NOTA: Assumiamo che i grafi siano connessi
//prodotto scalare tra booleani
std::optional<bool> prodotto_scalare(const std::vector<bool>& S, const std::vector<bool>& P){
    auto N_s = S.size();
    auto N_p = P.size();
    //non posso effettuare il prodotto scalare tra vettori di dimensioni diverse
    if (N_s != N_p){
        return std::nullopt;
    }
    int sum = 0;
    for (size_t i = 0; i < N_s; i++){
        if (S[i]&&P[i]){
            //se sono entrambe vere (true = 1), posso sommare a 1;
            sum++;
        }
    }
    //dobbiamo restituire il modulo due della somma
    return (sum%2==1);
}
//differenza simmetrica tra vettori booleani
std::optional<std::vector<bool>> differenza_simmetrica(const std::vector<bool>& S, const std::vector<bool>& P){
    auto N_s = S.size();
    auto N_p = P.size();
    //non posso effettuare il prodotto scalare tra vettori di dimensioni diverse
    if (N_s != N_p){
        return std::nullopt;
    }
    std::vector<bool> res(N_s); //vettore del risultato
    for (size_t i = 0; i< N_s; i++){
        res[i] = S[i]^P[i]; //XOR
    }
    return res;
}
//creo una struttura per gestire i nodi nel lifting (passaggio 1)
template <typename T>
struct lifted_node{
    T nodo_originale; 
    bool sign; //+ = true = 1, - = false = 0
    //costruzione di un operatore di confronto < 
    bool operator<(const lifted_node& other) const{
        if (nodo_originale != other.nodo_originale){
            return nodo_originale < other.nodo_originale;
        }
        return sign < other.sign;
    }
    //costruzione di un operatore di confronto ==
    bool operator==(const lifted_node& other) const{
        return nodo_originale == other.nodo_originale && sign == other.sign;
    }
};
//lifting 
template <typename T>
undirected_graph<lifted_node<T>> lifting(const undirected_graph<T>& G, const std::vector<bool>& S){
    //passaggio 1
    //i nodi andranno duplicati --> lifted_node per gestione
    auto archi = G.all_edges();
    auto m = archi.size();
    //passaggio 2
    undirected_graph<lifted_node<T>> G_prime;
    for (size_t i = 0; i < m; i++){
        T u = archi[i].from();
        T v = archi[i].to();
        if (S[i] == true){
            G_prime.add_edge({u, true}, {v, false});
            G_prime.add_edge({u, false}, {v, true});
        }
        else{
            G_prime.add_edge({u, true}, {v, true});
            G_prime.add_edge({u, false}, {v, false});
        }
    }
    
return G_prime;
}
//find minimal cycle
template <typename T> 
std::vector<bool> find_minimal_cycles(const undirected_graph<T>& G, const std::vector<bool>& S){
    auto G_primo = lifting(G, S); //passaggio 1+2
    //Inizializzazione di variabili che torneranno utili nel passaggio 5
    std::vector<bool> best_cycle; //miglior ciclo trovato
    size_t min_ones = std::numeric_limits<size_t>::max();
    //passaggio 3
    auto nodi_G = G.all_nodes();
    for (const auto& v : nodi_G){
        lifted_node<T> inizio = {v, true}; //v+
        lifted_node<T> arrivo = {v, false}; //v-
        //troviamo il cammino minimo con Dijkstra
        auto path = get_shortest_path(G_primo, inizio, arrivo);
        //passaggio 4
        if(!path.empty()){
            //costruzione del vettore di incidenza C
            std::vector<bool> C(S.size(), false);
            for(size_t j = 0; j < path.size()-1; j++){
                //creazione dell'arco originale dei due nodi consecutivi nel cammino
                undirected_edge<T> e_orig(path[j].nodo_originale, path[j+1].nodo_originale);
                //cerco e_orig in G
                auto idx_opt = G.edge_number(e_orig);
                if (idx_opt){
                    /*fare la somma modulo 2 equivale a "invertire" l'arco, 
                    quindi a usare XOR combinandolo con true*/
                    auto idx = *idx_opt;
                    C[idx] = C[idx]^ true;
                }
            }
            //passaggio 5
            size_t ones = 0;
            for (bool b : C){
                if (b){
                    ones ++;
                }
            }
            if(ones > 0 && ones < min_ones){ //deve esserci almeno un arco
                min_ones = ones;
                best_cycle = C;
            }
        }

    }
    return best_cycle; //restituzione del miglior ciclo trovato
}
//algoritmo di De Pina
template <typename T>
std::vector<std::vector<bool>> de_pina(const undirected_graph<T>& G){
    auto all_nodes = G.all_nodes();
    if (all_nodes.empty()){
        //vuoto
        return {}; 
    }
    auto all_edges_G = G.all_edges();
    const unsigned int m = all_edges_G.size();
    const unsigned int n = all_nodes.size();
    const unsigned int k = m - n + 1; //numero di cicli fondamentali
    auto dfsg = recursive_dfs(G, all_nodes[0]);
    auto C = G-dfsg; //coalbero
    //per come è stato costruito undirected_edge, gli archi (u,v) sono tali per cui u < v
    auto all_edges_C = C.all_edges(); //per come è costruito all_edges() è già ordinato
    std::vector<std::vector<bool>> S(k, std::vector<bool>(m,false)); //inizializzo il vettore di vettorei delle S_i
    for (unsigned int i = 0; i < k; i++){
        //devo cercare se l'arco è in G
        auto idx_opt = G.edge_number(all_edges_C[i]); 
        if (idx_opt){
            S[i][*idx_opt] = true; //Assegno il valore true nella posizione in S[i] corrispondente all'indice dell'arco presente anche in G
        }
    }
    //creo il vettore dei vettori di incidenza H_i
    std::vector<std::vector<bool>> H(k); 
    for (unsigned int i = 0; i < k; i++){
        std::vector<bool> Ci = find_minimal_cycles(G, S[i]);
        H[i] = Ci; 
        for (auto j = i+1; j < k; j++){
            auto ps_opt = prodotto_scalare(Ci, S[j]);
            //per costruzione di Ci e S[j], sappiamo che ps_opt ha valore,  quindi possiamo evitare di usare un if(ps_opt.has_value())
            if(*ps_opt ==1){
                auto diff = differenza_simmetrica(S[j], S[i]);
                //per costruzione, so che diff.has_value() restituisce true, quindi:
                S[j] = *diff;
            }
        }
    }
return H;
}
template <typename T> 
std::vector<T> bool_cycle_to_nodes(const std::vector<bool>& cycle, const undirected_graph<T>& G){
    auto all_e = G.all_edges();
    std::map<T, std::vector<T>> adj;
    T start;
    bool trovato = false;
	size_t edge_cont = 0; //contatore
    for (size_t i = 0; i < cycle.size(); i++){
        if (!cycle[i]) continue;
        edge_cont ++; //per contare gli archi attivi
        T u = all_e[i].from();
        T v = all_e[i].to();
        adj[u].push_back(v);
        adj[v].push_back(u);
        if (!trovato){ 
            start = u;
            trovato = true; }
    }
    if (!trovato) return {}; //mantenuto per il caso di ciclo di false 

    std::vector<T> path(edge_cont + 1);//percorso intrapreso: ci sono tanti nodi quanto il numero di archi + 1 (devo chiudere il ciclo)
    T curr = start;
    T prev = T(); 
    size_t idx_path = 0;
    bool primo_passo = true;
    bool ciclo_aperto = true;
    while (ciclo_aperto){
        path[idx_path++] = curr; //assegnazione del nodo corrente e post-incremento
        T prox;
        bool found_prox = false;
        for (T nb : adj[curr]){
            //evitare di tornare indietro sull'arco precedente
            if (primo_passo || nb != prev){
                // non tornare subito al punto di partenza se il ciclo non ha almeno due rami distinti
                if (nb == start && idx_path < 3) continue;
                prox = nb;
                found_prox = true;
                break;
            }
        }
        if (!found_prox){ //non viene mai raggiunto in condizioni normali di utilizzo
            //vicolo cieco
            ciclo_aperto = false;
        }
        else if (prox == start){
            //ciclo si chiude in maniera naturale
            path[idx_path] = start;
            ciclo_aperto = false;
            curr = prox; //curr == start per il prossimo check
        }
        else{
            //continuo a camminare
            prev = curr;
            curr = prox;
            primo_passo = false;
        }
    }
    if (curr != start){ //check finale di corretta chiusura
        //ciclo aperto
        return {};
    }
    
    return path;
}
    