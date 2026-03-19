#include <iostream>
#include <algorithm>
#include <cmath>
int main()
{
    static const int N = 10;
    double ad[N]= {0,1.2,3.3,4.6,7.8,8.9,9.2,6.8,6.4,8.9};
    double sum = 0.0;
    for (int i = 0; i < N ;i++) {
        sum = sum + ad[i];
    }
    double avr = sum/N;
    std::cout << "La media temperature: " << avr << "\n";
    
    double max_valore = ad[0];
    double min_valore = ad[0];
    for (int c=1;c<N;c++) {
        max_valore = std::max(max_valore, ad[c]);
        min_valore = std::min(min_valore ,ad[c]);
    }
    std::cout << "Il massimo è" << max_valore << "\n";
    std::cout << "Il minimo è" << min_valore << "\n";

    //calcolo deivazione standard
    double somma = 0.0;
    for (int r= 0; r<N; r++) {
        somma = somma + (ad[r] - avr)*(ad[r] - avr);
    }
    double sigma_2 = somma/N;
    double sigma = std::sqrt(sigma_2);
    std::cout << "la deviazione standard è" << sigma << "\n";
    return 0;
}