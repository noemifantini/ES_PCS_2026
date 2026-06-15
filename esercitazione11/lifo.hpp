#pragma once
#include <stack>
#include <optional>
/*La classe std::stack è un adattatore di contenitore che fornisce le funzionalità di uno 
stack, ovvero una struttura dati LIFO (Last In First Out).
Adatto ciò ai metodi put, get, empty*/
template <typename T>
class lifo{
    std::stack<T> s;
    public:
        //costruttore di default
        lifo() = default;
        //metodo put
        void put(const T& el){
            s.push(el);
        }
        //empty
        bool empty() const{
            return s.empty();
        }
        //get
        std::optional<T> get(){
	        if (s.empty()){
		        return std::nullopt;
		    }
            T val = s.top(); 
            s.pop();
            return val;
        }
};
