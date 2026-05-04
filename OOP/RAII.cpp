#include <bits/stdc++.h>
using namespace std;

// Resource acquisition is initialization
class Test
{
    
    public:
    int *m_iptrArr{nullptr};
    Test(int size)
    {
        // Allocating resource in constructor
        m_iptrArr = new int[size];
    }

    ~Test()
    {
        // Deallocating resorces
        delete[] m_iptrArr;
    }
};

int fun(int *arr)
{
    return 1;
}

// Example 1 Fail to apply RAII
int Example1()
{
    // Allocating memory of 40 bytes dynamically
    int *arr = new int[10];

    int retVal = fun(arr);

    if (retVal == -1)
        return 0; // if programms exits from here then there will be memory leaks

    cout << retVal << endl;

    delete[] arr;
    arr = NULL;
}

int main()
{
    Test *ptobjTest = new Test(5);

    ptobjTest->m_iptrArr[0];
    
    return 0;
}