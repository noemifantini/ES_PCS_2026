#include <concepts>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

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
            if (A[j]<A[j-1]){ //se invertiti faccio il cambio
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
//insertion su sottarrey
template<class T>
void insertion_sort(std::vector<T>& A, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        T key = A[i];
        int j = i - 1;
        while (j >= low && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
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

// algorimto merge

template <typename T>
void merge(std::vector<T>& A, int p, int q, int r)
{
    int n1 = q - p + 1;   // lunghezza del sottoarray sx
    int n2 = r - q;       // lunghezza del sottoarray dx

    // copia in vettori
    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];       // copia in L

    for (int j = 0; j < n2; j++)
        R[j] = A[q + j + 1];   // copia  in R

    int i = 0;   // indice  in L
    int j = 0;   // indice in R
    int k = p;   // indice in A

    //PRENDI IL MINORE
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // copia gli elementi in L)
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // copia gli elementi  in R 
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// merge sort ricorsivo
template <typename T>
void merge_sort(std::vector<T>& A, int p, int r){
    
    if (p >= r)
        return;

    int q =(p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
}

//partition
template <typename T>
int partition(std::vector<T>& A, int p, int r){
    T x = A[r]; //pivot come ultimo elemento
    int i = p-1;
        for (int j = p; j<r; j++){
            if (A[j] <= x){ //el minore di pivot aumento di caselle e metto in casella giusta
                i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);      //pivot in pos giusta
    return i + 1;
}


//implemetnazione quick sort
template <typename T>
void quick_sort(std::vector<T>& A, int p, int r){
    int N = A.size();
    if (N == 0){
        return;
    }
    if (p<r){
        int q = partition(A,p,r);
        quick_sort(A, p,q-1);
        quick_sort(A,q+1,r);
    }
}

//quick sort modificato
template <typename T>
void quick_sort_hybrid(std::vector<T>& A, int l, int h){
    int SOGLIA = 180; //fisso una soglia
    while (l<h){
        if (h-l +1 < SOGLIA){
            insertion_sort(A,l,h);
            break;
        }
        else{
            int pivot = partition(A, l,h);
            if (pivot - l < h-pivot){
                quick_sort_hybrid(A, l, pivot-1);
                l = pivot +1;
            }
            else{
                quick_sort_hybrid(A, pivot+1, h);
                h = pivot-1;
            }
        }
    }
}







    