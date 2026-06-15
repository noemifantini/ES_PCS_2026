#pragma once
#include <optional>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "undirected_edge.hpp"
/*classe che legge file di testo prende in input una stringa e 
viene passata direttamente alla classe che legge il file*/
/*In informatica, il parsing è il processo che converte una sequenza di dati 
in un formato strutturato e comprensibile*/
class netlist{
    char tipo_;
    std::string nome_;
    double valore_;
    int nodo1_;
    int nodo2_;
	/*private di default*/
	public:
    //costruttore di default
    netlist()
        : tipo_(' '), nome_(""), valore_(0.0), nodo1_(0), nodo2_(0)
    {}
    //costruttore di netlist
    netlist(const std::string& name, const double& val, const int& n1, const int& n2) {
    // Check sul tipo: deve iniziare con R o V 
    if (name.empty() || (std::toupper(name[0]) != 'R' && std::toupper(name[0]) != 'V')) {
        // Se non è valido, costruiamo una netlist "vuota" (stato di default)
        tipo_ = ' '; 
        nome_ = "";
        valore_ = 0.0;
        nodo1_ = 0;
        nodo2_ = 0;
    } else {
        // Se è valido, assegniamo i valori corretti
        tipo_ = std::toupper(name[0]);
        nome_ = name;
        valore_ = val;
        nodo1_ = n1;
        nodo2_ = n2;
    }
}
    //getter
    char tipo() const { return tipo_; }
    std::string nome() const { return nome_; }
    double valore() const { return valore_; }
    int nodo1() const { return nodo1_; }
    int nodo2() const { return nodo2_; }
    //funzione per dire se la riga letta è valida o no
    bool is_valid() const {
        if (tipo_ == 'R' || tipo_ == 'V'){
            return true;
        }
        return false;
    }
    //operatore per il confronto di netlist
    bool operator== (const netlist& other) const{
        double tol = 1e-12; //tolleranza per il confronto tra double
        if (other.nome() != nome_ || std::abs(other.valore()- valore_)> tol || other.nodo1() != nodo1_ || other.nodo2() != nodo2_){
            return false;
        }
        return true;
    }
    bool operator!= (const netlist& other) const{
        return !(*this==other);
    }
};
//operatore << per la stampa
std::ostream& operator<< (std::ostream& os, const netlist& nl){
    os << "(" << nl.tipo() << ", " << nl.nome() << ", " << nl.valore() << ", " << nl.nodo1() << ", " << nl.nodo2() <<")\n";
    return os;
}