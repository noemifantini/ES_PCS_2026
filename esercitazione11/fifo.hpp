#pragma once
#include <queue>
#include <optional>
/*La clase std::queue è un adattatore di contenitore che fornisce le funzionalità di una 
coda, ovvero una struttura dati FIFO (First In First Out).
Adatto ciò ai metodi put, get, empty*/
template <typename T>
class fifo{
    std::queue<T> q;
    public:
        //costruttore di default
        fifo() = default;
        //put
        void put(const T& el){
            q.push(el);
        }
        bool empty() const{
            return q.empty();
        }
        //get
        std::optional<T> get(){
	        if (q.empty()){
		        return std::nullopt;
		    }
            T val = q.front();
            q.pop();
            return val; 
        }
    
};