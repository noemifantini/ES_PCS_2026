#pragma once
#include <iostream>

template<typename T>
class undirected_edge {
    T m_from; // inizio
    T m_to;   // fine

public:
    // ordino arco in modo che a<=b
    undirected_edge(const T& a, const T& b) {
        if (a <= b) {
            m_from = a;
            m_to = b;
        } else {
            m_from = b;
            m_to = a;
        }
    }

    T from() const { return m_from; }
    T to()   const { return m_to; }

    // confronta archi
    bool operator<(const undirected_edge& e) const {
        if (m_from != e.m_from)
            return m_from < e.m_from;
        return m_to < e.m_to;
    }

    // se uguali
    bool operator==(const undirected_edge& e) const {
        return m_from == e.m_from && m_to == e.m_to;
    }

    // se diversi
    bool operator!=(const undirected_edge& e) const {
        return !(*this == e);
    }
};

// fuori dalla classe
template<typename T>
std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& e) {
    os << "(" << e.from() << " -- " << e.to() << ")";
    return os;
}