#include "number_util.h"
#include <cmath>
using namespace std;


bool is_prime(int i)
{
    int d {0} ,m {0};
    i = abs(i);
    m= static_cast <int> (ceil(sqrt(i))); /*to the square root of the number*/
    /*
    divide i by all these numbers one by one
    stop at the first complete division
    */
    if(i>2){
        for (d=2;d<=m;d++){
            if (i%d==0){
                return false;
            }
        }
    }
    return true;
}
vector <int> prime_factors(int n)
{
    int mul_identity = n<0?-1:1;
    n = abs(n);
    vector <int> factors {};
    if(is_prime(n)){
        factors.push_back(n);
    }
    else{
        int d {};
        for (d=2;d<=n;){
            if (is_prime(d)){
                if (n%d==0){ //find out if n could be divided by d
                    n = n/d;
                    factors.push_back(d);
                    continue;
                }
            }
            d++;
        }
    }
    factors.push_back(mul_identity);
    if(mul_identity==-1)
          factors.push_back(-mul_identity);
    return factors;
}
