#include <iostream>
#include <vector>
#include <algorithm>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"
#include <fstream>
int main() {
    timecounter tc;
    randfiller rf;      //riempio vettori
    const int m = 5000;  //nr di vettori su cui fare la media tempo
    std::ofstream file("tempi.csv");

    if (!file.is_open()) {
        std::cerr << "Errore apertura file\n";
        return 1;
    }
    file << "n,bubble,insertion,selection,merge,quick,stdsort\n";

    std::vector<int> dim;
    int nd = 50;        //numero di dimensione da testare
    dim.resize(nd);     //ridimensione il vettore a 50 elementi
    for (int i = 0; i < nd; i++) //riempio con valori 
        dim[i] = (i + 1) * 2;
    std::vector<double> t_bubble_all(nd);
    std::vector<double> t_insertion_all(nd);
    std::vector<double> t_selection_all(nd);
    std::vector<double> t_merge_all(nd);
    std::vector<double> t_quick_all(nd);
    std::vector<double> t_std_all(nd);

    for (int i = 0; i < nd; i++) {
        int n = dim[i];     //dimensione del vettore
        std::cout << "N=" << n << "\n";
        //ora devo crare m vettori di dim n
        std::vector<std::vector<int>> vecs(m, std::vector<int>(n));
        for (int r = 0; r < m; r++)
            rf.fill(vecs[r], -10000, 10000);          // numeri casuali

        // Bubble Sort
        std::vector<std::vector<int>> copie_b = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) bubble_sort(copie_b[r]);
        t_bubble_all[i] = tc.toc()/m;        //tempio medio in ms
        std::cout << "Bubble Sort:    " << t_bubble_all[i] << " s\n";
        
        // Insertion Sort
        std::vector<std::vector<int>> copie_i = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) insertion_sort(copie_i[r]);
        t_insertion_all[i] = tc.toc() / m;
        std::cout << "Insertion Sort: " << t_insertion_all[i] << " s\n";

        // Selection Sort
        std::vector<std::vector<int>> copie_s = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) selection_sort(copie_s[r]);
        t_selection_all[i] = tc.toc()/ m;
        std::cout << "Selection Sort: " << t_selection_all[i] << " s\n";

        // Merge Sort
        std::vector<std::vector<int>> copie_m = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) merge_sort(copie_m[r], 0, (int)copie_m[r].size() - 1);
        t_merge_all[i] = tc.toc()/ m;
        std::cout << "Merge Sort:     " << t_merge_all[i] << " s\n";

        // Quick Sort
        std::vector<std::vector<int>> copie_q = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) quick_sort(copie_q[r], 0, (int)copie_q[r].size() - 1);
        t_quick_all[i] = tc.toc()/ m;
        std::cout << "Quick Sort:     " << t_quick_all[i] << " s\n";

        // std::sort
        std::vector<std::vector<int>> copie_std = vecs;
        tc.tic();
        for (int r = 0; r < m; r++) std::sort(copie_std[r].begin(), copie_std[r].end());
        t_std_all[i] = tc.toc()/ m;
        std::cout << "std::sort:      " << t_std_all[i] << " s\n";

        file << n << "," << t_bubble_all[i] << "," << t_insertion_all[i] << "," << t_selection_all[i]
        << "," << t_merge_all[i] << "," << t_quick_all[i]<< "," << t_std_all[i] << "\n";
        if(t_insertion_all[i] > t_quick_all[i] ){
            std::cout << "\nPer n = " << dim[i] << "\nil quickosort è più veloce dell'insertion sort\n";
        }
        std::cout << "\n";
    }
    file.close();

    std::cout << "\nRicerca della soglia n0 \n";
    bool found = false;

    for (int i = 0; i <nd; i++){
        double best_quad = std::min({t_bubble_all[i],t_insertion_all[i],t_selection_all[i]});
        double best_log = std::min({t_merge_all[i],t_quick_all[i]});
        if (best_log < best_quad){
            std::cout << "n0 = " <<dim[i]<<"\n";
            found = true;
            break;
        }
    }
    if (! found){
        std::cout <<"n0 non trovato \n";
    }


    return 0;
}