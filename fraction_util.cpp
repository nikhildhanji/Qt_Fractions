#include <cmath>
#include <algorithm>
#include <string>
#include "fraction_util.h"
#include "number_util.h"
using namespace std;

void display (vector <int>& v){
    size_t c {0};
    cout<<"[";
    for (c=0;c < v.size()-1;c++)
        cout <<v.at(c)<<" x ";
    cout<<v.at(c)<<"]\n";
}
Fraction reduce (const Fraction &f){
    int n = f.numerator;
    int d = f.denominator;
    int common_factor {1};
    vector <int> n_prime_factors = prime_factors(n);
    vector <int> d_prime_factors = prime_factors(d);
    //cout<<"\nPrime factors ["<<n<<"]: ";
    //display(n_prime_factors);
    //cout<<"\nPrime factors ["<<d<<"]: ";
    //display(d_prime_factors);
    vector <int> common_prime_factors;
    std::sort(n_prime_factors.begin(), n_prime_factors.end());
    std::sort(d_prime_factors.begin(), d_prime_factors.end());

    std::set_intersection(n_prime_factors.begin(),n_prime_factors.end(),
                          d_prime_factors.begin(),d_prime_factors.end(),
                          back_inserter( common_prime_factors));
    //display( common_prime_factors);
    for(const int _c: common_prime_factors){
        common_factor *= _c;
    }
    Fraction rf {n/common_factor, d/common_factor};
    return rf;
}
std::string stringify (const Fraction &f){
    std::string str;
    //save the sign
     string sign = get_sign(f);
     //we'll do the reduce to lowest terms here
    Fraction rf = reduce(f);
    int n = rf.numerator;
    int d = rf.denominator;
    n = abs(n);
    d = abs(d);
    if (n==0 )
        str.assign(std::to_string(n));
    else if(d==1)
        str.assign(sign)
             .append(std::to_string(n));
     else if(n < d)
        str.assign(sign)
            .append(std::to_string(n))
            .append("/")
            .append(std::to_string(d));
    else  if (n==d)
         str.assign(sign)
             .append(std::to_string(1));
    else{
            int r = n % d;
            int w = n/d;
           str.assign(sign)
               .append(std::to_string(w))
               .append(" ")
               .append(std::to_string(r))
               .append("/")
               .append(std::to_string(d));
    }
    return str;
}
std::ostream &operator<<(std::ostream &os, const Fraction &rhs){
    os<<stringify(rhs);
    return os;
}
int LCM(int i, int j){
    int c {1};
    while (1){
        if ((i * c)%j == 0)
            return i * c;
        c++;
    }
}
int get_GCD(const Fraction& f1, const Fraction& f2){
    if(f1.denominator ==f2.denominator){
        return f1.denominator;
    }
    else{
        if(f1.denominator > f2.denominator){
           return f1.denominator % f2.denominator == 0?f1.denominator:LCM(f1.denominator, f2.denominator);
        }
        else{
           return f2.denominator % f1.denominator == 0?f2.denominator:LCM(f2.denominator, f1.denominator);
        }
    }
}
Fraction operator+(const Fraction& f1, const Fraction &f2){
    int gcd = get_GCD(f1, f2);
    Fraction resultant { (gcd/f1.denominator) * f1.numerator + (gcd/f2.denominator) * f2.numerator,gcd};
    return resultant;
}
Fraction operator-(const Fraction& f1, const Fraction &f2){
    int gcd = get_GCD(f1, f2);
    Fraction resultant { (gcd/f1.denominator) * f1.numerator - (gcd/f2.denominator) * f2.numerator,gcd};
    return resultant;
}
Fraction operator*(const Fraction& f1, const Fraction & f2){
    Fraction resultant {f1.numerator * f2.numerator, f1.denominator * f2.denominator};
    return resultant;
}
Fraction operator/(const Fraction& f1, const Fraction & f2) throw (std::invalid_argument){
    Fraction resultant {f1.numerator * f2.denominator, f2.numerator * f1.denominator};
    return resultant;
}
bool operator<(const Fraction& f1, const Fraction & f2){
    int gcd = get_GCD(f1, f2);
    return (gcd/f1.denominator) * f1.numerator <  (gcd/f2.denominator) * f2.numerator;
}
bool operator>(const Fraction& f1, const Fraction & f2){
    int gcd = get_GCD(f1, f2);
    return (gcd/f1.denominator) * f1.numerator >  (gcd/f2.denominator) * f2.numerator;
}
bool operator==(const Fraction& f1, const Fraction & f2){
    int gcd = get_GCD(f1, f2);
    return (gcd/f1.denominator) * f1.numerator ==  (gcd/f2.denominator) * f2.numerator;
}
bool operator!=(const Fraction& f1, const Fraction & f2){
    int gcd = get_GCD(f1, f2);
    return (gcd/f1.denominator) * f1.numerator !=  (gcd/f2.denominator) * f2.numerator;
}
std::string to_string (Fraction& ref){
    return get_sign (ref) + std::to_string(abs(ref.numerator)) + "/"+ std::to_string(abs(ref.denominator));
}
std::string get_sign (Fraction f){
    int n = f.numerator;
    int d = f.denominator;
    string sign = positive_sign;
    if(static_cast<float>(n)/d<0)
        sign = negative_sign;
    return sign;
}
