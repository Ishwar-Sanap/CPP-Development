///************************************************************************* */
/// @file clsMathUtils.h
/// @author: Ishwar Sanap
/// @date: 06-July-2025
/// @brief file declaring the class structure and member functions of clsMathUtils class
///
///************************************************************************** */

#include <vector>

#define MAX_NUM 1000

class clsMathUtils
{
private:
    std::vector<int> m_primes;

    // Helper function to find the prime numbers
    void getSieve(int num);

public:
    /// @brief: clsMathUtils constructor
    clsMathUtils();

    /// @brief clsMathUtils destructor
    ~clsMathUtils();

    ///************************************************************************* */
    /// @fn: isPrime(int)
    /// @author: Ishwar Sanap
    /// @date: 06-July-2025
    /// @input: positive integer number
    /// @return true if number if prime, else false
    ///
    ///************************************************************************** */
    bool isPrime(int num);

#ifdef ADVANCED_API
    ///************************************************************************* */
    /// @fn: getGCD(int,int)
    /// @author: Ishwar Sanap
    /// @date: 06-July-2025
    /// @input: positive integer numbers
    /// @return integer GCD of given two number
    ///
    ///************************************************************************** */
    int getGCD(int num1, int num2);

    ///************************************************************************* */
    /// @fn: getLCM(int,int)
    /// @author: Ishwar Sanap
    /// @date: 06-July-2025
    /// @input: positive integer numbers
    /// @return integer LCM of given two number
    ///
    ///************************************************************************** */
    int getLCM(int num1, int num2);
#endif
};