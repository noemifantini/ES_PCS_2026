#include "gradiente_coniugato.hpp"
#include <iostream>
#include <Eigen/Dense>

// funzione helper: controlla che A*x == b entro tolleranza
bool soluzione_corretta(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x)
{
    return (b - A * x).norm() < 1.0e-8;
}

int main()                                    
{
    // sistema 2x2
    Eigen::MatrixXd A(2, 2);
    A << 4, 1,                               
         1, 3;                              

    Eigen::VectorXd a(2);                     
    a << 6, 7;                               
    auto x_a = gradiente_coniugato(A, a);    

    if (!x_a.has_value()) {              
        std::cerr << "errore\n";            
        return EXIT_FAILURE;                 
    }
//CONTROLLO 
    if (!soluzione_corretta(A, a, x_a.value())) {  
        std::cerr << "errore\n";             
        return EXIT_FAILURE;
    }

    std::cout << "2x2 " << "risultato corretto\n"; 

    // Test 3x3
    Eigen::MatrixXd A3(3, 3);
    A3 << 4, 1, 0,
          1, 3, 1,
          0, 1, 2;
 
    Eigen::VectorXd b3(3);
    b3 << 5, 9, 7;
 
    auto x_b = gradiente_coniugato(A3, b3);
    if (!x_b.has_value()) {
        std::cerr << "3x3: errore\n";
        return EXIT_FAILURE;
    }
    //errore se errata
    if (!soluzione_corretta(A3, b3, x_b.value())) {
        std::cerr << "3x3: errore\n";
        return EXIT_FAILURE;
    }
    std::cout << "3x3 risultato corretto\n";
 

    // Test matrice NON quadrata
    Eigen::MatrixXd A_nq(2, 3);
    A_nq << 1, 2, 3,
            4, 5, 6;
 
    Eigen::VectorXd b_nq(2);
    b_nq << 1, 2;
 
    auto x_nq = gradiente_coniugato(A_nq, b_nq);
    if (x_nq.has_value()) {
        std::cerr << "non quadrata deve restituire nullopt\n";
        return EXIT_FAILURE;
    }
    std::cout << "non quadrata: errore corretto \n";
 
    //NON simmetrica
    // ci aspettiamo nullopt
    Eigen::MatrixXd A_ns(3, 3);
    A_ns << 4, 1, 0,
            9, 3, 1,   
            0, 1, 2;
 
    Eigen::VectorXd b_ns(3);
    b_ns << 1, 2, 3;
 
    auto x_ns = gradiente_coniugato(A_ns, b_ns);
    if (x_ns.has_value()) {
        std::cerr << "non simmetrica: doveva restituire nullopt!\n";
        return EXIT_FAILURE;
    }
    std::cout << "non simmetrica: errore rilevato correttamente\n";
 
    //matrice singolare
    // ci aspettiamo nullopt
    Eigen::MatrixXd A_sing(3, 3);
    A_sing << 1, 2, 3,
              2, 4, 6,   
              3, 6, 9;
 
    Eigen::VectorXd b_sing(3);
    b_sing << 1, 2, 3;
 
    auto x_sing = gradiente_coniugato(A_sing, b_sing);
    if (x_sing.has_value()) {
        std::cerr << "singolare: doveva restituire nullopt!\n";
        return EXIT_FAILURE;
    }
    std::cout << "singolare: errore rilevato correttamente\n";
 
    return 0;
}
