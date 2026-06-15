#include "netlist.hpp"
#include "grafi_netlist.hpp"
#include <Eigen/Eigen>
#include "build_matrici.hpp"
#include "cicli_min_dfs.hpp"
#include "de_pina.hpp"
#include "undirected_graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gradiente_coniugato_prog.hpp"


int main(int argc, const char* argv[]){
    auto circ_opt = read_file(argc, argv);
    if(circ_opt){
        auto C = *circ_opt; //otteniamo il circuito
        std::cout <<"Scegliere il metodo per il calcolo dei cicli minimi: \n";
        std::cout <<"1) DFS (cicli fondamentali, la minimalità non è garantita)\n";
        std::cout <<"2) De Pina (cicli minimi)\n";
        std::cout <<"Scelta (1 o 2):\n";
        int scelta;
        std::cin >> scelta;
        //check sulla scelta
        if(scelta != 1 && scelta != 2){
            std::cerr <<"Scelta non valida\n";
            return 1;
        }
        auto e = C.G.all_edges().size();
        auto n_nodi = C.G.all_nodes().size();
        auto k = e - n_nodi + 1;
        std::vector<std::vector<int>> cicli(k);
        if (scelta == 1){
            //DFS
            cicli = find_fundamental_cycles(C.G);
        }
        else{
            //De Pina
            auto cicli_bool = de_pina(C.G);
            for (size_t i = 0; i < k; i++){
                cicli[i] = bool_cycle_to_nodes(cicli_bool[i], C.G);
          		}
        }
        //definizione delle matrici
        auto B = build_B(C, cicli);
        auto R = build_R(C);
        auto v = build_v(C, cicli);
        //matrice dei coefficienti
        auto A = build_mat_coeff(B,R);
        //gradiente coniugato
        
        auto I = gradiente_coniugato(A, v);
        //calcolo della legge di Ohm
        auto v_r = R*B*I; //calcolo della tensione sui resistori
        auto i_r = B*I; //vettore delle correnti reali sui resistori
        //Output
        for (int i = 0; i < (int)C.R.size(); ++i){
            double V = v_r(i); //tensione della resistenza
            double corr = i_r(i);
            std::cout << C.R[i].nome() << ": V = " << V << " volts, I = " << corr <<" amps.\n";
        }
        return 0;
    }
    return 1;
}
