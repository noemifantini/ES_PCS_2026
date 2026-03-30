#include <iostream>
#include "rational2.hpp"

int main() {
    rational<int> a(1, 2);
    rational<int> b(2, 4);
    rational<int> c(3, 6);  
    rational<int> d(-3, -6); 
    rational<int> e(3, -6);  
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";
    std::cout << "d = " << d << "\n";
    std::cout << "e = " << e << "\n";

    rational<int> x(1, 3);
    rational<int> y(1, 6);

    std::cout << "\nOperazioni:\n";
    std::cout << x << " + " << y << " = " << (x + y) << "\n"; 
    std::cout << x << " - " << y << " = " << (x - y) << "\n"; // 1/6

    rational<int> m(2, 3);
    rational<int> n(3, 4);
    std::cout << m << " * " << n << " = " << (m * n) << "\n"; 
    std::cout << m << " / " << n << " = " << (m / n) << "\n"; 
    

    rational<int> pos_inf(1, 0);        //attribuisco io il valore a pos_inf
    rational<int> neg_inf(-1, 0); 
    rational<int> nan(0, 0);       
    std::cout << "pos_inf = " << pos_inf << "\n";
    std::cout << "neg_inf = " << neg_inf << "\n";
    std::cout << "nan     = " << nan << "\n";
//faccio le varie operazioni
    std::cout << pos_inf << " + " << x    << " = " << (pos_inf + x)    << "\n";
    std::cout << pos_inf << " + " << neg_inf << " = " << (pos_inf + neg_inf) << "\n"; 
    std::cout << pos_inf << " + " << pos_inf << " = " << (pos_inf + pos_inf) << "\n"; 
    std::cout << pos_inf << " - " << pos_inf << " = " << (pos_inf - pos_inf) << "\n"; 
    std::cout << pos_inf << " * " << x    << " = " << (pos_inf * x)    << "\n"; 
    std::cout << pos_inf << " * " << neg_inf << " = " << (pos_inf * neg_inf) << "\n"; 
    std::cout << neg_inf << " * " << neg_inf << " = " << (neg_inf * neg_inf) << "\n"; 

    std::cout << nan << " + " << x      << " = " << (nan + x)      << "\n"; 
    std::cout << nan << " * " << pos_inf << " = " << (nan * pos_inf) << "\n";

//attribuisco io valore e faccio ancora una prova di operazione di somma con semplificazione
    rational<int> k(6, 3); 
    rational<int> p(5, 1); 
    std::cout << "6/3 = " << k << "\n"; // 2
    std::cout << "5/1 = " << p << "\n"; // 5
    std::cout << k << " + " << p << " = " << (k + p) << "\n"; 

    return 0;
}
