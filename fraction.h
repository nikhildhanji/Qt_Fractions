#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <stdexcept>
class Fraction
{
    friend std::ostream &operator<<(std::ostream &, const Fraction &);
    friend Fraction operator+(const Fraction&, const Fraction &);
    friend Fraction operator-(const Fraction&, const Fraction &);
    friend Fraction operator*(const Fraction&, const Fraction &);
    friend Fraction operator/(const Fraction&, const Fraction &)throw (std::invalid_argument);
    friend bool operator<(const Fraction&, const Fraction &);
    friend bool operator>(const Fraction&, const Fraction &);
    friend bool operator==(const Fraction&, const Fraction &);
    friend bool operator!=(const Fraction& f1, const Fraction & f2);
    friend int get_GCD(const Fraction&, const Fraction&);
    friend Fraction reduce (const Fraction &);
    friend std::string get_sign (Fraction );
    friend std::string to_string (Fraction&);
    friend std::string stringify (const Fraction &);

private:
    int numerator;
    int denominator;
public:
    Fraction(int n, int d=1) throw (std::invalid_argument);
    ~Fraction() = default;
    float get_value();
    Fraction& operator=(const Fraction&);
    Fraction& inverse() throw (std::invalid_argument);
};

#endif // FRACTION_H
