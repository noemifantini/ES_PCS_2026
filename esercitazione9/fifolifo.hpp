#pragma once
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <vector>    
#include <limits>  
#include <optional>

// contenitore LIFO - stack
template<typename T>
class lifo {
    std::stack<T> m_stack; // contenitore vuoto
public:
    // costruttore di default
    lifo() = default;
//inserisco elemento in cima
    void put(const T& x) {
        m_stack.push(x);
    }
//estraggo ultimo elemento 
    T get() {
        T x = m_stack.top();
        m_stack.pop();
        return x;
    }
//se stack vuoto
    bool empty() {
        return m_stack.empty();
    }
};


// contenitore FIFO- coda
template<typename T>
class fifo {
    std::queue<T> m_queue; // contenitore vuoto
public:
    // costruttore di default
    fifo() = default;
//inserisco elemento in fondo alla coda
    void put(const T& x) {
        m_queue.push(x);
    }
//estraggo primo elemento inserito
    T get() {
        T x = m_queue.front();
        m_queue.pop();
        return x;
    }

    bool empty() const{
        return m_queue.empty();
    }
};


