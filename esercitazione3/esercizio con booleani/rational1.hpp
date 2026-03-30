#pragma once
#include <concepts>
#include <numeric>
#include <ostream>
//uguale alla cartella 'senza bool' ma in questa ho utilizzato i booleani
template<typename I> requires std::integral<I>
class rational{
    I num_;
    I den_;
    void reduce(){
        if (den_ < 0){      // denominatore sempre positivo deve essere, quindi cambio segni
            num_ = -num_ ;
            den_ = -den_;
        }
        if (den_ == 0) {
            return;          //se den è zero fermo la funzione
        }
        if (num_ == 0){     // diventa 0/1
            den_ = 1;
            return;
        }
        I g = std::gcd(num_, den_); // ho trovato la funzione su C++reference, calcolo massimo comune divisore
        num_ = num_ / g;
        den_ = den_ /g;
    }
    bool is_nan() const {           //creo booleani se num e den sono zero restituisce vero (nan) altrimenti falso 
        if (num_ == I{0} && den_== I{0}){
            return true;
            }
        return false;
    }
    bool is_pinf() const{       // anche in quelli sotto creo booleani +inf se nume >0 e den = 0
        if(num_>I{0} && den_ == I{0}){
            return true;
        }
        return false;
    }
    bool is_minf() const{       //meno inf
        if (num_<I{0} && den_ == I{0}){
            return true;
        }
        return false;
    }
    bool is_fin() const{        //finito
        if( den_ != I{0}){
            return true;
        }
        return false;
    }
    public:
        rational()
            : num_(I{0}), den_(I{1})        //inizializzo
        {}
        rational(const I& n, const I& d)
            : num_(n), den_(d)
        {

            if (d != I{0}) {
                reduce();
            }      
        }
    I num() const {return num_;}            //legge
    I den() const {return den_; }
    rational& operator+=(const rational& other) {
        if (is_nan() || other.is_nan()){
            num_ = I{0};
            den_ = I{0};
            return *this;
        }
        if ((is_pinf() || is_minf()) && (other.is_pinf() || other.is_minf())){
            if ((is_pinf()&& other.is_minf()) || (is_minf() && other.is_pinf())){
                num_ = I{0};  
                return *this;  
            }
            return *this;       // is_pinf controlla se numeratore è +inf, mentre is_minf se è -inf e mi da +inf o  -inf
        }

        if (is_pinf() || is_minf()){
            return *this; 
        }

        if (other.is_pinf() || other.is_minf()){  //other infinito
            num_ = other.num_;
            den_ = I{0};
            return *this;
        }

        num_ = num_*other.den_ + other.num_*den_;        // (a*d + c*b)/b*d = a/b + c/d
        den_ = den_ * other.den_;
        reduce();
        return *this;
    }

    rational operator+(const rational& other) const{
        rational ret = *this;
        ret += other;
        return ret;
    }
    rational& operator-=(const rational& other) {
        rational minus_other(-other.num_, other.den_);
        *this += minus_other;       // sarebbe -other
        return *this;
    }
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }
    rational& operator*=(const rational& other) {

        if (is_nan() || other.is_nan()){
            num_ = I{0};
            den_ = I{0};
            return *this;
        }
        // 0 * Inf = NaN (indet), Inf * 0 = NaN
        if ((num_ == I{0} && (other.is_pinf() || other.is_minf())) || ((is_pinf()|| is_minf())&& other.num_ == I{0})) {
            num_ = I{0};
            den_ = I{0};
            return *this;
        }

        if ((is_pinf()||is_minf())|| (other.is_pinf()||other.is_minf())) {

            bool positivo = (num_*other.num_ > I{0});
            if (positivo) {
                num_ = I{1};
                den_ = I{0}; 
                return *this;
            }
            else{
                num_ = I{-1};
                den_ = I{0};
                return *this;
            }
        }
        num_ = num_*other.num_;     // a/b * c/d = a*c / d*b
        den_ = den_*other.den_;
        reduce();
        return *this;
    }

    rational operator*(const rational& other) const{
        rational ret = *this;
        ret = ret *= other;
        return ret;
    }

    rational& operator/=(const rational& other) {
//divisione la vedo come reciproco e quindi diventa prodotto
        rational reciproco(other.den_, other.num_);
        *this *= reciproco;
        return *this;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret = ret /= other;
        return ret;
    }
};

template <typename I> requires std::integral<I>
std::ostream& 
operator<<(std::ostream &stream, const rational<I>& frazione){
    bool nan (frazione.num() == I{0} && frazione.den()== I{0});
    bool pinf (frazione.num()>I{0} && frazione.den() == I{0});
    bool minf (frazione.num()<I{0} && frazione.den()==I{0});
    bool nint (frazione.den()==I{1});
    if (nan){
        stream <<"NaN";
    }
    else if (pinf){
        stream << "+Inf";
    }
    else if (minf){
        stream << "-Inf";
    }
    else if (nint){
        stream << frazione.num();
    }
    else{
        stream << frazione.num()<<"/"<<frazione.den();
    }
    return stream;
}