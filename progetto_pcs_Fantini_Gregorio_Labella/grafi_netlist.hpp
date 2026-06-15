#pragma once
#include "netlist.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <optional>
#include<sstream>
#include <map>
#include <string>
/*Vogliamo costruire una funzione che, preso in input un vettore di netlist (output di read_file())
restituisca un grafo costruito a partire dalle netlist e una struttura contenente l'informazione sull'indice (il segno viene ottenuto lavorando con la maglia)
e sulle componenti del circuito */
//per prima cosa creiamo una struttura circuito
struct circuito{
    //il primo elemento è un grafo ottenuto dalla netlist
    undirected_graph<int> G; //i nodi sono tutti interi
    //Elenco di resistori e generatori
    std::vector<netlist> R;
    std::map<undirected_edge<int>, double> V; //dei generatori interessa solo l'informazone arco-valore; il segno viene registrato in segno
    //Una mappa che associa a ogni arco l'indice di posizione
    //std::map<undirected_edge<int>, int> indice;
    //una mappa che assegna a ogni arco il segno del generatore (+1, -1)
    std::map<undirected_edge<int>, int> segno;
    private:
        /*In una struttura tutti i dati sono pubblici di default; 
        tuttavia, vogliamo proteggere add_componente da modifiche al di fuori della struct*/
        void add_componente(const int n1,const int n2){
            //quando aggiungiamo una componente, indipendentemente dal tipo
            undirected_edge<int> e(n1, n2);
            G.add_edge(n1,n2); //aggiornamento del grafo
            //sia nel caso delle resistenze sia nel caso dei generatori occorre aggiornare segno e grafo
            //assumiamo che non ci siano cappi
            //registriamo l'informazione sul segno
            if (n1 < n2){
                segno[e] = +1;
            }
            else{
                //percorro in senso opposto
                segno[e] = -1;
            }
            /*costruire gli indici dinamicamente dopo ogni inserimento può essere decisamente oneroso...posso farlo in read_indici dopo ave letto tutto
            il file --> build_indici()*/

        }
    public:
        void add_resistenza(const netlist& nl){
            //aggiungiamo al grafo + informazione sul segno
            add_componente(nl.nodo1(), nl.nodo2());
            //aggiorniamo le resistenze
            R.push_back(nl); //a priori non si sa quante saranno le resistenze
        }
        void add_generatore(const netlist& nl){
            //aggiungiamo al grafo + informazione sul segno
            add_componente(nl.nodo1(), nl.nodo2());
            //aggiorniamo i generatori
            V[undirected_edge(nl.nodo1(), nl.nodo2())] = nl.valore(); 
        }
        /*void build_indici(){
            auto archi = G.all_edges(); //ordine lessicografico garantito
            for (size_t i = 0; i < archi.size(); ++i){
                indice[archi[i]] = i;
            }
        }*/
        
    
};
//funzione che legge un file di input e restituisce il  il circuito
std::optional<circuito> read_file(int argc, const char *argv[]){
    if (argc < 2) {
        std::cerr << "ERRORE: filename non specificato\n";
        return std::nullopt;
    }
    if (argc > 2){
        std::cerr << "ERRORE: sono stati specificati più filename\n";
        return std::nullopt;
    }
    std:: ifstream ifs(argv[1]);
    //check sull'apertura del gile
    if(!ifs.is_open()){
        std::cerr << "ERRORE: file " << argv[1] <<" non trovato\n";;
        return std::nullopt;
    }
    //creaiamo un circuito sulla base del contenuto del file
    circuito C;
    std::string linea;
    int num_riga = 0;
    //Non possiamo avere resistenze in parallelo
    std::set<undirected_edge<int>> R_archi; //creiamo un set in cui raccogliamo gli archi collegati a una resistenza 
    while (std::getline(ifs, linea)) {
        ++num_riga;
        //occorre per ogni riga "estrarre" i dati di interesse
        //creiamo uno stream associato alla singola linea
        std::istringstream iss(linea);
        std::string name;
        /*La riga di soli spazi non è gestita da linea.empty(), usiamo un check su name*/
        if (!(iss >> name)){
            //std::cout << "Riga vuota\n";
            continue; //ignoro la linea vuota
        }
        double val;
        int n1;
        int n2;
        if(!(iss >> val >> n1 >> n2)){
            std::cerr << "Errore nel parsing della riga " << num_riga << "\n";
            continue;
        }
        netlist nl(name, val, n1, n2);
        if (!nl.is_valid()){
            //se la netlist non è valida viene ignorata
            std::cout << "Tipo '" << name[0] << "' non valido alla riga "<< num_riga << "\n";
            continue;
        }
        //procediamo alla lettura del circuito
        if (nl.tipo() == 'R'){
            undirected_edge<int> e(n1,n2);
            if (R_archi.find(e) != R_archi.end()){
                //se all'arco è già collegata una resistenza, lo scarto
                std::cout <<"All'arco "<< e << " è già collegata una resistenza\n";
                continue; 
                //passo oltre
            }
            R_archi.insert(e); //"registrazione" dell'arco come collegato a una resistenza
            C.add_resistenza(nl); //"registrazione della resistenza"
        }
        else{
            //altrimenti siamo di fronte a un generaotre
            C.add_generatore(nl);
        }
    }
    //terminato il ciclo occorre assegnare gli indici sugli archi
    //C.build_indici(); //grafo completo --> meno oneroso rispetto a ricalcolarlo volta per volta
    return C;
}