#include <iostream>
#include "gradiente_coniugato_prog.hpp"

int main() {

    // TEST della matrice identità
    {
        Eigen::MatrixXd A = Eigen::MatrixXd::Identity(3, 3);
        Eigen::VectorXd b(3);
        b << 1, 2, 3;

        Eigen::VectorXd x = gradiente_coniugato(A, b);

        double norma = (x - b).norm();
        std::cout << "Test 1 - matrice identita\n";
        std::cout << "  soluzione trovata: " << x.transpose() << "\n";
        std::cout << "  errore: " << norma << "\n";
        if (norma < 1e-10)
            std::cout << "  converge correttamente\n";
        else
            std::cout << "  ATTENZIONE: errore troppo grande\n";
    }

    std::cout << "\n";

    // TEST della matrice diagonale semplice
    {
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(3, 3);
        A(0,0) = 2;  A(1,1) = 4;  A(2,2) = 8;
        Eigen::VectorXd b(3);
        b << 2, 4, 8;

        Eigen::VectorXd x = gradiente_coniugato(A, b);

        double norma = (x - Eigen::VectorXd::Ones(3)).norm();
        std::cout << "Test 2 - matrice diagonale\n";
        std::cout << "  soluzione trovata: " << x.transpose() << "\n";
        std::cout << "  errore da [1,1,1]: " << norma << "\n";
        if (norma < 1e-10)
            std::cout << "  converge correttamente\n";
        else
            std::cout << "  ATTENZIONE: errore troppo grande\n";
    }

    std::cout << "\n";

    // TEST della matrice SPD 3x3
    {
        Eigen::MatrixXd A(3, 3);
        A << 4, 1, 0,
             1, 3, 1,
             0, 1, 2;
        Eigen::VectorXd b(3);
        b << 5, 4, 3;

        Eigen::VectorXd x = gradiente_coniugato(A, b);

        double norma = (b - A * x).norm();
        std::cout << "Test 3 - matrice SPD densa\n";
        std::cout << "  soluzione trovata: " << x.transpose() << "\n";
        std::cout << "  norma residuo: " << norma << "\n";
        if (norma < 1e-10)
            std::cout << "  converge correttamente\n";
        else
            std::cout << "  ATTENZIONE: residuo troppo grande\n";
    }

    return 0;
}