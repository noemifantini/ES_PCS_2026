#include "netlist.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
//test netlist
int main(){
    //costruttore di netlist
    netlist nl1("R1", 1.0, 1, 2);
    std::cout <<"nl1: "<< nl1 <<"\n";
    if (!nl1.is_valid()){
        std::cerr << "ERRORE: la netlist è stata ritenuta non valida\n";
        return EXIT_FAILURE;
    }
    //check sul 'getter'
    if (nl1.tipo()!= 'R'){
        std::cerr << "ERRORE: il tipo identificato non è corretto";
        return EXIT_FAILURE;
    }
    if (nl1.nome()!= "R1"){
        std::cerr << "ERRORE: il nome identificato non è corretto";
        return EXIT_FAILURE;
    }
    double tol = 1e-12; //tolleranza
    if (std::abs(nl1.valore()- 1.0)> tol){
        std::cerr << "ERRORE: il valore identificato non è corretto";
        return EXIT_FAILURE;
    }
    if (nl1.nodo1() != 1){
        std::cerr << "ERRORE: il nodo1 identificato non è corretto";
        return EXIT_FAILURE;
    }
    if (nl1.nodo2() != 2){
        std::cerr << "ERRORE: il nodo2 identificato non è corretto";
        return EXIT_FAILURE;
    }
    netlist nl2 ("V1", 1.0, 1, 3);
    std::cout <<"nl2: "<< nl2 <<"\n";
    if (!nl2.is_valid()){
        std::cerr << "ERRORE: la netlist è stata ritenuta non valida\n";
        return EXIT_FAILURE;
    }
    netlist nl3 ("C1", 1.0, 2, 3);
    std::cout <<"nl3: "<< nl3 <<"\n";
    if (nl3.is_valid()){
        std::cerr << "ERRORE: la netlist è stata ritenuta valida\n";
        return EXIT_FAILURE;
    }
    /*//test lettura file
    //file netlist_prova
    const char* argv1[] = {"test1", "netlist_prova.txt"};
    int argc1 = 2;
    netlist parser1;
    auto result1 = parser1.read_file(argc1, argv1);
    if(result1.has_value()){
        std::vector<netlist> circuito1 = *result1;
        if (circuito1.size() != 7){
            std::cerr << "ERRORE: numero di componenti errato\n";
            return EXIT_FAILURE;
        }
        for (const auto& nl : circuito1) {
            std::cout << "Letto: " << nl;
        }
    }
    else{
        std::cerr <<"ERRORE: il file non è stato letto correttamente\n";
        return EXIT_FAILURE;
    }
    //file netlist_esempio.txt
    const char* argv2[] = {"test2", "netlist_esempio.txt"};
    int argc2 = 2;
    netlist parser2;
    auto result2 = parser2.read_file(argc2, argv2);
    if(result2.has_value()){
        std::vector<netlist> circuito2 = *result2;
        if (circuito2.size() != 5){
            std::cerr << "ERRORE: numero di componenti errato\n";
            return EXIT_FAILURE;
        }
        for (const auto& nl : circuito2) {
            std::cout << "Letto: " << nl;
        }
    }
    else{
        std::cerr <<"ERRORE: il file non è stato letto correttamente\n";
        return EXIT_FAILURE;
    }
    //test se argcv è maggiore di 2
    const char* argv3[] = {"test3", "netlist_esempio.txt", "netlist_prova.txt"};
    int argc3 = 3;
    netlist parser3;
    auto result3 = parser3.read_file(argc3, argv3);
    if (result3.has_value()){
        std::cerr <<"ERRORE: legge un file quando l'input non è valido\n";
        return EXIT_FAILURE;
    }
    //file test_errore_v.txt
    const char* argv4[] = {"test4", "test_errore_v.txt"};
    int argc4 = 2;
    netlist parser4;
    auto result4 = parser4.read_file(argc4, argv4);
    //salta la riga vuota
    if (result4.has_value()){
        auto nl4 = *result4;
        if (nl4.size() == 1){
            if (nl4[0] != netlist("R1", 100.0, 0, 1)){
                std::cerr <<"ERRORE nella lettura del file\n";
                return EXIT_FAILURE;
            }
        }
        else{
        std::cerr <<"ERRORE nella lettura del file\n";
        return EXIT_FAILURE;}
    }
    else{
        std::cerr << "ERRORE: il file dovrebbe essere letto\n";
        return EXIT_FAILURE;
    }
    //file test_no_double.txt
    const char* argv5[] = {"test5", "test_no_double.txt"};
    int argc5 = 2;
    netlist parser5;
    auto result5 = parser5.read_file(argc5, argv5);
    if (result5.has_value()){
        auto nl5 = *result5;
        if (nl5.size() == 1){
            if (nl5[0] != netlist("V2", 0.9, 2, 3)){
                std::cerr <<"ERRORE nella lettura del file\n";
                return EXIT_FAILURE;
            }
        }
        else{
            std::cerr <<"ERRORE nella lettura del file\n";
            return EXIT_FAILURE;}
    }
    else{
        std::cerr << "ERRORE: il file dovrebbe essere letto\n";
        return EXIT_FAILURE;
    }
    //test nome insesistente
    const char* argv6[] = {"test6", "netlistttttt.txt"};
    int argc6 = 2;
    netlist parser6;
    auto result6 = parser6.read_file(argc6, argv6);
    if (result6.has_value()){
        std::cerr <<"ERRORE: legge un file quando l'input non esiste\n";
        return EXIT_FAILURE;
    }
    //test sulle resistenze su test_valido.txt
    const char* argv7[] = {"test7", "test_valido.txt"};
    int argc7 = 2;
    netlist parser7;
    auto result7 = parser7.read_file(argc7, argv7);
    //salta la seconda resistenza
    if (result7.has_value()){
        auto nl7 = *result7;
        if (nl7.size() == 1){
            if (nl7[0] != netlist("R1", 100.0, 0, 1)){
                std::cerr <<"ERRORE nella lettura del file\n";
                return EXIT_FAILURE;
            }
        }
        else{
        std::cerr <<"ERRORE nella lettura del file (non trascura la seconda resistenza)\n";
        return EXIT_FAILURE;}
    }
    else{
        std::cerr << "ERRORE: il file dovrebbe essere letto\n";
        return EXIT_FAILURE;
    }*/
    return EXIT_SUCCESS;
}