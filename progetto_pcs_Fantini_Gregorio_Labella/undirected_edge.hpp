#pragma once
#include <iostream>
#include <algorithm>
template <typename T>
class undirected_edge{
    T m_from;
    T m_to;
    public:
        undirected_edge(T a, T b){
            //ordine from < to
            m_from = std::min(a,b);
            m_to = std::max(a,b);
        }
        T from() const {
            return m_from;
        }
        T to() const{
            return m_to;
        }
        
        //per evitare ambiguità uso friend
        friend std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& e){
            return os << "(" << e.from() << "; " << e.to()<<")";
        }
        //ordinamento lessicografico
        bool operator< (const undirected_edge<T>& e) const{
            if (*this!= e){
                if (m_from != e.m_from){
                    return m_from < e.m_from;
                }
                return m_to < e.m_to;
            }
            return false;
        }
        bool operator== (const undirected_edge<T>& e) const{
            return m_from == e.m_from && m_to == e.m_to;
        }
        bool operator!= (const undirected_edge& e) const{
            return !(*this == e);
        }
    
};

