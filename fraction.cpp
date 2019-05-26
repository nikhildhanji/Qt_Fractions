#include "fraction.h"

Fraction::Fraction(int numerator, int denominator) throw (std::invalid_argument)
    : numerator{numerator}, denominator{denominator}
{
    if(denominator == 0){
        throw std::invalid_argument{"Denominator cannot be zero"};
    }
}

float Fraction::get_value(){
    return static_cast<float>(numerator)/denominator;
}
Fraction& Fraction::operator=(const Fraction& f){
    this->numerator = f.numerator;
    this->denominator = f.denominator;
    return *this;
}
Fraction& Fraction::inverse() throw (std::invalid_argument){
    int n = this->numerator;
    int d =  this->denominator;
    n=n+d;
    d=n-d;
    n=n-d;
    if(d==0)
        throw std::invalid_argument{"Denominator cannot be zero"};
    this->numerator = n;
    this->denominator = d;
    return *this;
}
