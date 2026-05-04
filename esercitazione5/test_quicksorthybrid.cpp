#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <random>
#include <algorithm>   // std::is_sorted
#include "sorts.hpp"
#include "randfiller.h"

int main(){
    randfiller generato;

    // ── TEST SU 100 VETTORI DI INT CASUALI ───────────────────────────────────
    std::cout << "Test su 100 vettori casuali di int...\n";
    for (int t = 0; t < 100; t++) {
        int dimensione = rand() % 101;
        std::vector<int> v(dimensione);
        generato.fill(v, -100, 100);

        if (!v.empty())
            quick_sort_hybrid(v, 0, (int)v.size()-1);

        if (!std::is_sorted(v.begin(), v.end())) {
            std::cerr << "ERRORE: Test fallito al vettore " << t+1 << "\n";
            return EXIT_FAILURE;
        }
    }
    std::cout << "SUCCESSO: tutti i vettori di int ordinati correttamente\n\n";

    // ── TEST SU VETTORI DI STRINGHE ──────────────────────────────────────────
    std::cout << "Test su vettori di stringhe...\n";

    std::vector<std::string> mesi     = {"gennaio", "febbraio", "marzo", "aprile",
                                          "maggio", "giugno", "luglio", "agosto",
                                          "settembre", "ottobre", "novembre", "dicembre"};
    std::vector<std::string> stagioni = {"primavera", "estate", "autunno", "inverno"};
    std::vector<std::string> giorni   = {"lunedi", "martedi", "mercoledi", "giovedi",
                                          "venerdi", "sabato", "domenica"};

    quick_sort_hybrid(mesi,     0, (int)mesi.size()-1);
    quick_sort_hybrid(stagioni, 0, (int)stagioni.size()-1);
    quick_sort_hybrid(giorni,   0, (int)giorni.size()-1);

    if (!std::is_sorted(mesi.begin(),     mesi.end()))
        { std::cerr << "ERRORE quick sort hybrid su mesi\n";     return EXIT_FAILURE; }
    if (!std::is_sorted(stagioni.begin(), stagioni.end()))
        { std::cerr << "ERRORE quick sort hybrid su stagioni\n"; return EXIT_FAILURE; }
    if (!std::is_sorted(giorni.begin(),   giorni.end()))
        { std::cerr << "ERRORE quick sort hybrid su giorni\n";   return EXIT_FAILURE; }

    std::cout << "SUCCESSO: tutti i vettori di stringhe ordinati correttamente\n\n";

    std::cout << "Tutti i test superati con SUCCESSO!\n";
    return EXIT_SUCCESS;
}