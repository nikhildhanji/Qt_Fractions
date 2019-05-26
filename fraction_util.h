#ifndef FRACTION_UTIL_H
#define FRACTION_UTIL_H
#include "fraction.h"
#include <vector>
static constexpr const char* negative_sign = "-";
static constexpr const char* positive_sign = "";
std::ostream &operator<<(std::ostream &, const Fraction &);
std::string stringify (const Fraction &);
int get_GCD(const Fraction&, const Fraction&);
Fraction operator+(const Fraction&, const Fraction &);
Fraction operator-(const Fraction&, const Fraction &);
Fraction operator*(const Fraction&, const Fraction &);
Fraction operator/(const Fraction&, const Fraction &)throw (std::invalid_argument);
bool operator<(const Fraction&, const Fraction &);
bool operator>(const Fraction&, const Fraction &);
bool operator==(const Fraction&, const Fraction &);
bool operator!=(const Fraction& f1, const Fraction & f2);

Fraction reduce (const Fraction &);
std::string to_string (Fraction&);
std::string get_sign (Fraction );
#endif // FRACTION_UTIL_H
