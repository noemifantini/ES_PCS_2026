#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <optional>

std::optional<Eigen::VectorXd> gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b)
{                                                  
    const double tol = 1.0e-15;

    // matrice quadrata
    int n_righe   = A.rows();
    int n_colonne = A.cols();
    if (n_righe != n_colonne) {
        return std::nullopt;
    }
//controllo se matrice singolare
    if (std::abs(A.determinant()) < tol) {
        return std::nullopt;
    }

    // matrice simmetrica
    if (!A.isApprox(A.transpose())) {
        return std::nullopt;
    }

    // matrice definita positiva
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(A); 
    auto autovalori = solver.eigenvalues();                    
    if (autovalori.minCoeff() < tol) {
        std::cout << "la matrice non e' definita positiva\n";  
        return std::nullopt;                                   
    }

    // vettore inizializzato con zero
    Eigen::VectorXd x = Eigen::VectorXd::Zero(n_righe);
//residuo e direzioni iniziali
    Eigen::VectorXd res = b - A * x;
    Eigen::VectorXd p   = res;

    const double res_norm_0       = res.norm();
    const double res_tol          = 1.0e-12;
    const unsigned int it_max     = 10000;
    unsigned int it               = 0;

    while (it < it_max && res.norm() > res_tol * res_norm_0)
    {
        const Eigen::VectorXd Ap = A * p;
        //calcolo passo alpha
        const double pAp   = (p.transpose() * Ap).value();
        const double alpha = (p.transpose() * res).value() / pAp;
        //aggiorno sol
        x = x + alpha * p;
        Eigen::VectorXd res_nuovo = b - A * x; //nuovo residuo
        //calcolo beta
        const double beta = (p.transpose() * A * res_nuovo).value() / pAp;
        //nuova direzione p
        p   = res_nuovo - beta * p;
        //avanzamento iterazione
        res = res_nuovo;
        it++;
    }

    return x;
}