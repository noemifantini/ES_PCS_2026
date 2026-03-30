#pragma once
#include <concepts>
#include <ostream>
#include <numeric>

template<typename I> requires std::integral<I> 
class rational 
{ 
    I num_; 
    I den_; 

    void reduce()
    {
        if (den_ < 0) {     // denominatore sempre positivo deve essere, quindi cambio segni 
            num_ = -num_;       
            den_ = -den_;
        }
        if (den_ == I{0}) {     //se den è zero fermo la funzione
            return; 
        }
        if (num_ == I{0}) {     // diventa 0/1
            den_ = I{1};
            return;
        }
        I g = std::gcd(num_, den_);     //caso  standard, calcolo massimo comune divisore (ho trovato la funzione nella libreria)
        num_ = num_ / g;
        den_ = den_ / g;
    }

public:
    rational()
        : num_(I{0}), den_(I{1})
    {}

    rational(const I& n, const I& d)
        : num_(n), den_(d)
    {
        if (d != I{0}) {
            reduce();
        }
    }

    I num() const { return num_; }      //legge
    I den() const { return den_; }

    rational& operator+=(const rational& other) {

        if ((num_ == I{0} && den_ == I{0}) || (other.num_ == I{0} && other.den_ == I{0})) {
            num_ = I{0};
            den_ = I{0};
            return *this;   //esce subito, rimane 0/0
        }

        if ((num_ != I{0} && den_ == I{0}) && (other.num_ != I{0} && other.den_ == I{0})) {
            if ((num_ > I{0} && other.num_ < I{0}) || (num_ < I{0} && other.num_ > I{0})) {
                num_ = I{0};
                den_ = I{0};            //risultato indeterminato
                return *this;   
            }

            return *this;
        }

        if (num_ != I{0} && den_ == I{0}) {
            return *this;
        }

        if (other.num_ != I{0} && other.den_ == I{0}) {
            num_ = other.num_;
            den_ = I{0};
            return *this;
        }
        num_ = num_ * other.den_ + other.num_ * den_;       // (a*d + c*b)/b*d = a/b + c/d
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    rational operator+(const rational& other) const {       //esegue
        rational ret = *this;
        ret += other;
        return ret;
    }

    rational& operator-=(const rational& other) {
        rational minus_other(-other.num_, other.den_);      //trasformo in somma
        *this += minus_other;  // sarebbe -other
        return *this;
    }

    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational& operator*=(const rational& other) {

        if ((num_ == I{0} && den_ == I{0}) || (other.num_ == I{0} && other.den_ == I{0})) {
            num_ = I{0};
            den_ = I{0};
            return *this;         
        }
        // 0 * Inf = NaN (indet), Inf * 0 = NaN
        if ((num_ == I{0} && other.den_ == I{0}) || (den_ == I{0} && other.num_ == I{0})) {
            num_ = I{0};
            den_ = I{0};
            return *this;
        }
    
        if (den_ == I{0} || other.den_ == I{0}) {
            bool same_sign = (num_ > I{0}) == (other.num_ > I{0});
            num_ = same_sign ? I{1} : I{-1};    // inf*inf con i segni corretti
            den_ = I{0};
            return *this;
        }

        num_ = num_ * other.num_;
        den_ = den_ * other.den_;       // a/b * c/d = a*c / d*b
        reduce();
        return *this;
    }

    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    rational& operator/=(const rational& other) {
        rational reciproco(other.den_, other.num_);     //divisione la vedo come reciproco e quindi diventa prodotto
        *this *= reciproco;
        return *this;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};


template <typename I> requires std::integral<I>
std::ostream& 
operator<<(std::ostream& stream, const rational<I>& frazione)
{
    if (frazione.den() == I{0}) {
        if (frazione.num() == I{0}) {
            stream << "NaN";
        } else if (frazione.num() > I{0}) {
            stream << "+Inf";
        } else {
            stream << "-Inf";
        }
    } else if (frazione.num() == I{0}) {
        stream << 0;
    } else if (frazione.den() == I{1}) {
        stream << frazione.num();
    } else {
        stream << frazione.num() << "/" << frazione.den();
    }
    return stream;
}
