#pragma once
#include <Eigen/Dense>
#include <vector>
#include <map>

//costruire B
Eigen::MatrixXd build_B (const circuito& C, const std::vector<std::vector<int>>& cicli){
    //dimensioni
    int m = C.R.size(); //numero resistenze
    int n = cicli.size(); //numero maglie
    //inizializziamo la matrice nulla
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m,n);
    //scorriamo sui cicli
    for (int j = 0; j < n; ++j){
        const auto& ciclo = cicli[j]; //creiamo un riferimento per ottimizzare in memoria
        //sappiamo che non è degenere
        for (size_t k = 0; k < ciclo.size()-1; ++k){
            int u = ciclo[k]; //primo nodo
            int v = ciclo[k+1]; //secondo nodo
            undirected_edge<int> e_ciclo(u,v);
            //controlliamo che a tale arco sia associata una resistenza
            for (int i = 0; i < m; i++){
                undirected_edge<int> e_r(C.R[i].nodo1(), C.R[i].nodo2());
                if (e_r == e_ciclo){
                    //all'arco è collegata una resistenza
                    if (u <v){
                        //u < v --> segno concorde
                        B(i,j) = +1.0;
                    }
                    else{
                        B(i,j) = -1.0;
                        //per costruzione non ci sono cappi
                    }
                    break; //riga trovata, passiamo oltre
                }
            }
        }
    }
    return B;
}

//costruire R
Eigen::MatrixXd build_R(const circuito& C){
    auto m = C.R.size();
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m,m);
    for (size_t i = 0; i < m; i++  ){
        R(i,i) = C.R[i].valore();
    }
    return R; //ritorniamo la matrice diagonale
}
//costruire v
Eigen::VectorXd build_v(const circuito& C, const std::vector<std::vector<int>>& cicli){
    int n = cicli.size(); //dimensione
    //inizializziamo un vettore di 0
    Eigen::VectorXd v = Eigen::VectorXd::Zero(n);
    for (int j = 0; j < n; ++j){
        const auto& ciclo = cicli[j];
        for (size_t k = 0; k < ciclo.size() -1; ++k){
            int u = ciclo[k]; //nodo 1
            int w = ciclo[k+1]; //nodo 2
            //creo l'arco per poi controllare se è collegato a un generatore
            undirected_edge<int> e(u,w); //ordina from<to
            //cerco tra i generatori
            auto it = C.V.find(e);
            if (it != C.V.end()){
	            //c'è generatore collegato
	            //segno della maglia
	            int segno_maglia;
                    if (u < w){
                        segno_maglia = -1;
                    }
                    else{
                        segno_maglia = +1;
                        //non sono ammessi cappi per costruzione
                    }
                //prelevo segno del generatore
                int segno_gen = C.segno.at(e);
                int segno_complessivo = segno_gen*segno_maglia;
                //dereferenzio il puntatore ed estraggo il valore
                const double valore = it->second;
                v(j) += valore*segno_complessivo;
               }

    }
    }
    return v;
}

//costruire matrice coefficienti
Eigen::MatrixXd build_mat_coeff(const Eigen::MatrixXd& B, const Eigen::MatrixXd& R){
    return B.transpose()*R*B;
}