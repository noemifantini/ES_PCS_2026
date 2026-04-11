#include <iostream>
#include <vector>
#include <algorithm>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"


int main() {
    timecounter tc;     //misuro tempo
    randfiller rf;      //riempire vettore con numero randomico
    for (int n = 4; n <=8192; n*=2){
        std::vector<int> vettore(n);
        rf.fill(vettore,-1000,1000);
        std::cout <<"N=" << n <<"\n";
        if (n <= 32) {  //stampa il vettore solo se è piccolo (altrimenti troppi numeri)
            std::cout << "Vettore generato: [ ";
            for (int i = 0; i < (int)vettore.size(); ++i) {
                std::cout << vettore[i] << (i == (int)vettore.size() - 1 ? "" : ", ");
            }
            std::cout << " ]\n";
        }


        
        // Bubble Sort
        std::vector<int> vb = vettore; //creo copia del vettore
        tc.tic(); //inizio conteggio
        bubble_sort(vb);//richiamo funzione
        std::cout << "Bubble Sort: " << tc.toc() * 1000 << " ms\n"; //calcolo il tempo il ms

        // Insertion Sort
        std::vector<int> vi = vettore;
        tc.tic();
        insertion_sort(vi);
        std::cout << "Insertion Sort: " << tc.toc() * 1000 << " ms\n";

        // Selection Sort
        std::vector<int> vs = vettore;
        tc.tic();
        selection_sort(vs);
        std::cout << "Selection Sort: " << tc.toc() * 1000 << " ms\n";

        // std::sort
        std::vector<int> vstd = vettore;
        tc.tic();
        std::sort(vstd.begin(), vstd.end());
        std::cout << "std::sort: " << tc.toc() * 1000 << " ms\n";

    }

    return 0;
}
        
