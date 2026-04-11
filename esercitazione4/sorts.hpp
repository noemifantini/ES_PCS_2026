#include <concepts>
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
bool is_sorted(const std::vector<T>& v)
{
    if (v.size() == 0){     //vettore vuoto è ordinato
        return true;
    }
    for (int i = 1; i<(int)v.size(); i ++ ){
        if(v[i]<v[i-1]){
            return false;       //non ordinato, secondo elemento minore del primo 
        }
    }
    return true;
}

//Bubble Sort implementazione
template<typename T>
void bubble_sort(std::vector<T>& A)
{
    for (int i = 0; i<= (int)A.size()-2; i++){
        for(int j=(int)A.size() -1; j>= i+1; j--){
            if (A[j]<A[j-1]){
                std::swap(A[j],A[j-1]);
            }
        }
    }
}

//Insertion Sort implementazione
template<typename T> 
void insertion_sort(std::vector<T>& A)
{
    for (int j = 1; j< (int)A.size(); j++){
        T chiave = A[j];
        int i = j-1;
        while (i>= 0 && A[i]>chiave){
            A[i+1]=A[i];
            i = i-1;

        }
        A[i+1]=chiave;

    }
}

// implementazione selection_sort
template <typename T>
void selection_sort(std::vector<T>& A)
{

    int n = A.size();

    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;

        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            std::swap(A[i], A[min_index]);
        }
    }
}