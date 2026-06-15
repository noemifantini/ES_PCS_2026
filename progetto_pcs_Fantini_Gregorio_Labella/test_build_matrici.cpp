#include <iostream>
#include <vector>
#include <cmath> 
#include <Eigen/Dense>
#include "grafi_netlist.hpp"
#include "netlist.hpp"
#include "build_matrici.hpp"
#include "undirected_edge.hpp"
#include <string>

int main() {
    double tol = 1e-12;  //fisso una tolleranza per i confronti di double

    //creo un circuito
    circuito C;
    
    C.R.push_back(netlist("R1", 10.0, 1, 2));
    C.R.push_back(netlist("R2", 20.0, 2, 3));
    C.R.push_back(netlist("R3", 30.0, 2, 4)); 
    undirected_edge<int> e1(1,3);
    C.V[e1] = 10.0;
    undirected_edge<int> e2(4,3);
	C.V[e2] = 20.0;
	
	//assegno i segni a ciascun arco
    C.segno[undirected_edge<int>(1,2)] = +1;
	C.segno[undirected_edge<int>(2,3)] = +1;
	C.segno[undirected_edge<int>(2,4)] = +1;
	C.segno[undirected_edge<int>(1,3)] = +1;
	C.segno[undirected_edge<int>(4,3)] = -1;

    //definisco i cicli
	std::vector<int> C1 = {1, 2, 3, 1};
    std::vector<int> C2 = {4, 3, 2, 4};
    std::vector<std::vector<int>> cicli = {C1, C2};
    
    //test sulla matrice R
    Eigen::MatrixXd R = build_R(C);
    //verifica della dimensione
    if (R.rows() != 3 || R.cols() != 3) {
        std::cerr << "ERRORE: le dimensioni di R sono errate (" << R.rows() << "x" << R.cols() << " invece di 3x3)\n";
        return EXIT_FAILURE;
    }
    //verifica dei valori sulla diagonale
    if (std::abs(R(0,0) - 10.0) > tol || std::abs(R(1,1) - 20.0) > tol || std::abs(R(2,2) - 30.0) > tol) {
        std::cerr << "ERRORE in R: i valori sulla diagonale sono errati\n";
        return EXIT_FAILURE;
    }
    //verifica dei valori fuori dalla diagonale
    if (std::abs(R(0,1) - 0.0) > tol || std::abs(R(0,2) - 0.0) > tol || 
	    std::abs(R(1,0) - 0.0) > tol || std::abs(R(1,2) - 0.0) > tol || 
		std::abs(R(2,0) - 0.0) > tol || std::abs(R(2,1) - 0.0) > tol) {
        std::cerr << "ERRORE in R: ci sono elementi non nulli fuori dalla diagonale\n";
        return EXIT_FAILURE;
    }


    //test sulla matrice B
    Eigen::MatrixXd B = build_B(C, cicli);
    //check dimensioni
    if (B.rows() != 3 || B.cols() != 2) {
        std::cerr << "ERRORE: le dimensioni di B sono errate (" << B.rows() << "x" << B.cols() << " invece di 3x2)\n";
        return EXIT_FAILURE;
    }
	//check valori
    if (std::abs(B(0,0) - 1.0) > tol || std::abs(B(0,1) - 0.0) > tol ||
	    std::abs(B(1,0) - 1.0) > tol || std::abs(B(1,1) - (-1.0)) > tol || 
		std::abs(B(2,0) - 0.0) > tol || std::abs(B(2,1) - 1.0) > tol) {
        std::cerr << "ERRORE in B: i valori sono errati\n";
        return EXIT_FAILURE;
    }

    //test sul vettore v
    Eigen::VectorXd v = build_v(C, cicli);

    if (v.size() != 2) {
        std::cerr << "ERRORE: v ha dimensione errata\n";
        return EXIT_FAILURE;
    }
   
    if (std::abs(v(0) - (10.0)) > tol || std::abs(v(1) - (-20.0)) > tol) {
        std::cerr << "ERRORE in v: i valori non sono corretti\n";
        return EXIT_FAILURE;
    }

    //test sulla matrice dei coefficienti
    Eigen::MatrixXd mat_coeff = build_mat_coeff(B, R);

    if (mat_coeff.rows() != 2 || mat_coeff.cols() != 2) {
        std::cerr << "ERRORE nella matrice dei coefficienti: le dimensioni sono errate\n";
        return EXIT_FAILURE;
    }
    
    if (std::abs(mat_coeff(0,0) - 30.0) > tol || std::abs(mat_coeff(0,1) - (-20.0)) > tol ||
        std::abs(mat_coeff(1,0) - (-20.0)) > tol || std::abs(mat_coeff(1,1) - 50.0) > tol) {
        std::cerr << "ERRORE nella matrice dei coefficienti: i valori sono errati\n";
        return EXIT_FAILURE;
    }
    //secondo test
    circuito C3;
    C3.R.push_back(netlist("R1", 5.0, 1, 2));
    C3.R.push_back(netlist("R2", 10.0, 2, 3));
    C3.R.push_back(netlist("R3", 15.0, 3, 4));
    C3.R.push_back(netlist("R4", 20.0, 2, 5));
	undirected_edge<int> e3(4,1);
    C3.V[e3] = 12.0;
    undirected_edge<int> e4(5,3);
    C3.V[e4] = 8.0;

    C3.segno[undirected_edge<int>(1,2)] = +1;
    C3.segno[undirected_edge<int>(2,3)] = +1;
    C3.segno[undirected_edge<int>(3,4)] = +1;
    C3.segno[undirected_edge<int>(2,5)] = +1;
    C3.segno[undirected_edge<int>(4,1)] = +1;
    C3.segno[undirected_edge<int>(5,3)] = +1;

    std::vector<int> Ciclo1 = {1,2,3,4,1};
    std::vector<int> Ciclo2 = {2,5,3,2};
    std::vector<std::vector<int>> cicli3 = {Ciclo1,Ciclo2};
    //check su B
    auto B3 = build_B(C3, cicli3);
    if (std::abs(B3(0,0)-1.0) > tol || std::abs(B3(0,1)-0.0) > tol ||
    std::abs(B3(1,0)-1.0) > tol || std::abs(B3(1,1)+1.0) > tol ||
    std::abs(B3(2,0)-1.0) > tol || std::abs(B3(2,1)-0.0) > tol ||
    std::abs(B3(3,0)-0.0) > tol || std::abs(B3(3,1)-1.0) > tol)
    {
        std::cerr << "ERRORE in B3\n";
        return EXIT_FAILURE;
    }
    //test su v
    auto v3 = build_v(C3, cicli3);
    if (std::abs(v3(0)-12.0) > tol ||std::abs(v3(1)-8.0) > tol)
    {
        std::cerr << "ERRORE in v\n";
        return EXIT_FAILURE;
    }
    //test su R
    auto R3 = build_R(C3);
    // controllo dimensioni
    if (R3.rows() != 4 || R3.cols() != 4) {
        std::cerr << "ERRORE: le dimensioni di R sono errate ("
                << R3.rows() << "x" << R3.cols()
                << " invece di 4x4)\n";
        return EXIT_FAILURE;
    }
    // controllo elementi diagonali
    if (std::abs(R3(0,0) - 5.0) > tol ||
        std::abs(R3(1,1) - 10.0) > tol ||
        std::abs(R3(2,2) - 15.0) > tol ||
        std::abs(R3(3,3) - 20.0) > tol)
    {
        std::cerr << "ERRORE in R: valori diagonali errati\n";
        return EXIT_FAILURE;
    }
    // controllo elementi fuori diagonale
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j && std::abs(R3(i,j)) > tol) {
                std::cerr << "ERRORE in R: elemento fuori diagonale non nullo in posizione ("
                        << i << "," << j << ")\n";
                return EXIT_FAILURE;
            }
        }
    }
    std::cout << "Tutti i test sulle matrici sono stati superati con successo!\n";
    return EXIT_SUCCESS;
}