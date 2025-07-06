#include <iostream>
#include "clsMathUtils.h"
using namespace std;

int main()
{
    clsMathUtils obj;

    int n = 97;
    if (obj.isPrime(n))
        cout << n << " is prime number\n";

    else
        cout << n << " is not prime number\n";

    int gcd = obj.getGCD(12, 15);
    cout << "GCD of 12 & 15 : " << gcd << endl;

    int lcm = obj.getLCM(12, 15);
    cout << "LCM of 12 & 15 : " << lcm << endl;


    return 0;
}