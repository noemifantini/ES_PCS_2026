#pragma once
#include <set> 
#include <vector>
template <typename T>
std::set<std::set<T>> converti_in_set_set(const std::vector<std::vector<T>>& cicli){
    std::set<std::set<T>> res;
    for (const auto& ciclo : cicli){
        //inseriamo i nodi in un set per eliminare i duplicati (chiusura)
        std::set<T> ciclo_set(ciclo.begin(), ciclo.end());
        if (!ciclo_set.empty()){
            res.insert(ciclo_set);
        }
    }
    return res;
}