//test ausil_dfs
#include <iostream>
#include <vector>
#include <set>
#include "dfs_ausil.hpp"
int main(){
    //test sul vuoto
    std::vector<std::vector<int>> vuoto = {};
    auto res_vuoto = converti_in_set_set(vuoto);
    if (!res_vuoto.empty()){
        std::cerr <<"ERRORE: un input vuoto dovrebbe produrre un output vuoto\n";
        return EXIT_FAILURE;
    }
    //vettore di cicli vuoti
    std::vector<std::vector<int>> cicli_vuoti = {{},{}};
    auto res_c_v = converti_in_set_set(cicli_vuoti);
    if (!res_c_v.empty()){
        std::cerr <<"ERRORE: un input di cicli vuoti dovrebbe produrre un output vuoto\n";
        return EXIT_FAILURE;
    }
    //check rimozione chiusura
    std::vector<std::vector<int>> ciclo_chius = {{0,1,2,3,0}};
    auto res_chius = converti_in_set_set(ciclo_chius);
    std::set<std::set<int>> atteso_chius = {{0,1,2,3}};
    if (res_chius != atteso_chius){
        std::cerr <<"ERRORE nella gestione delle chiusure (duplicati)\n";
        return EXIT_FAILURE;
    };
    //indipendenza da ordine percorrenza
    std::vector<std::vector<int>> cicli_identici = {{0,1,2,0}, {2,1,0,2}, {1,2,0,1}};
    auto res_identici = converti_in_set_set(cicli_identici);
    if (res_identici.size() != 1){
        std::cerr << "ERRORE nella gestione di cicli in cui cambia l'ordine di percorrenza\n";
        return EXIT_FAILURE;
    }
    std::set<std::set<int>> atteso_id = {{0,1,2}};
    if (atteso_id !=  res_identici){
        std::cerr <<"ERRORE nell'output\n";
        return EXIT_FAILURE;
    }
    //caso misto
    std::vector<std::vector<int>> misto = {
        {0, 1, 2, 0},
        {},
        {3, 4, 5, 3},
        {}
    };
    auto res_misto = converti_in_set_set(misto);
    std::set<std::set<int>> atteso_misto = {{0, 1, 2}, {3, 4, 5}};
    if (atteso_misto != res_misto){
        std::cerr << "ERRORE nella gestione di input misti (vuoto e non)\n";
        return EXIT_FAILURE;
    }
    std::cout <<"Tutti i test sono stati superati con successo\n";
    return EXIT_SUCCESS;
}