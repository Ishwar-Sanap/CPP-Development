///************************************************************************* */
/// @file clsMathUtils.cpp
/// @author: Ishwar Sanap
/// @date: 06-July-2025
/// @brief File implements the member function of clsMathUtils class
///
///************************************************************************** */

#include "clsMathUtils.h"

clsMathUtils::clsMathUtils()
{
    getSieve(MAX_NUM);
}

clsMathUtils::~clsMathUtils()
{
}

void clsMathUtils::getSieve(int num)
{
    m_primes.clear();
    m_primes.assign(num + 1, 1);

    m_primes[0] = m_primes[1] = 0;
    for (int i = 2; (i * i) <= num; i++)
    {
        if (m_primes[i] == 1)
        {
            // marking the multiples of i, as non prime
            for (int j = i * i; j <= num; j += i)
            {
                m_primes[j] = 0;
            }
        }
    }
}
bool clsMathUtils::isPrime(int num)
{
    // using sieve of eranthrosese Algorithm to check prime in O(1)
    // But we have to perform precomputation first.. on max range
    // we have assume m_inum is the max possible range to check prime

    // If num is within the range of give num then in O(1) we can check the prime
    if (num <= MAX_NUM)
        return m_primes[num];
    else
    {
        // we have to follow the traditional way to check the prime O(sqrt(n))

        for (int i = 2; i * i <= num; i++)
        {
            if ((num % i) == 0)
                return 0;
        }
    }

    return 1;
}

// Euclidean Algorithm to find Greatest common divisor
int clsMathUtils::getGCD(int num1, int num2)
{
    if (num2 == 0)
        return num1;

    return getGCD(num2, num1 % num2);
}

// LCM : Lowest common multiple
int clsMathUtils::getLCM(int num1, int num2)
{
    // relation between GCD and LCM
    //  LCM(a, b) = (a x b) / GCD(a, b)

    return (num1 * num2) / getGCD(num1, num2);
}