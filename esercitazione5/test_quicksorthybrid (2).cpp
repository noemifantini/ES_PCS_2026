#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <random>
#include "sorts.hpp"
#include "randfiller.h"

int main(){
    randfiller generato;
    for (int t = 0; t<100;t++){     //100 vettori di prova
        int dimensione = rand() % 101;      //dimensione scelta a caso
        std::vector<int> v(dimensione);
        
        generato.fill(v,-100,100);
        merge_sort(v, 0, (int)v.size() -1);

        if (!is_sorted(v)){     //verificare che il vettore sia ordinato
            std::cerr << "ERRORE: Test fallito";
            return EXIT_FAILURE;
        }
    }
    std::cout << "SUCCESSO: Test corretto";

            // ── TEST SU VETTORI DI STRINGHE ──────────────────────────────────────────
    std::cout << "Test su vettori di stringhe...\n";

    std::vector<std::string> mesi     = {"gennaio", "febbraio", "marzo", "aprile",
                                          "maggio", "giugno", "luglio", "agosto",
                                          "settembre", "ottobre", "novembre", "dicembre"};
    std::vector<std::string> stagioni = {"primavera", "estate", "autunno", "inverno"};
    std::vector<std::string> giorni   = {"lunedi", "martedi", "mercoledi", "giovedi",
                                          "venerdi", "sabato", "domenica"};

    quick_sort(mesi,     0, (int)mesi.size()-1);
    quick_sort(stagioni, 0, (int)stagioni.size()-1);
    quick_sort(giorni,   0, (int)giorni.size()-1);

    if (!is_sorted(mesi))     { std::cerr << "ERRORE quick sort su mesi\n";     return EXIT_FAILURE; }
    if (!is_sorted(stagioni)) { std::cerr << "ERRORE quick sort su stagioni\n"; return EXIT_FAILURE; }
    if (!is_sorted(giorni))   { std::cerr << "ERRORE quick sort su giorni\n";   return EXIT_FAILURE; }
    std::cout << "OK\n\n";

    std::cout << "Tutti i test superati con SUCCESSO!\n";
    return EXIT_SUCCESS;

}