#include <iostream>
int main()
{ 
    static const int N = 10;
    double ad[N] = {0,1.2,1.3,3.4,4.6,7.8,8.9,9.2,6.8,6.4,};
    bool scambio = true;
    while (scambio){

    
        scambio = false;

        for (int i = 0; i < N -1 ; i ++){
            if (ad[i] > ad[i+1]){
                double temp = ad[i];
                ad[i] = ad[i+1];
                ad[i+1] = temp;
                scambio = true;
            }
    }
}
    std::cout << "Array ordinato:\n";
    for (int i=0; i < N; i++){
        std::cout <<ad[i] <<" ";

    }
    return 0;
}