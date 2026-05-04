#include <bits/stdc++.h>
using namespace std;

/*
Rule of 3
If your class manages a resource (like raw pointers, file handles, etc.), you should explicitly define the following three special member functions:
    1. Destructor
    2. Copy Constructor
    3.Copy Assignment Operator

// Above 3 and addition of 2 more : Rule of 5 (C++11)
    4. move constructor
    5. move assingnment operator
*/
class TestOp
{
public:
    int *m_iptrArr{nullptr};
    int m_iSize;
    TestOp(int size)
    {
        // Allocating resource in constructor
        m_iSize = size;
        m_iptrArr = new int[size];

        cout << "Default constructor siz : " << size << endl;
    }

    // 1) Copy constructor
    TestOp(const TestOp &otherObj)
    {
        this->m_iSize = otherObj.m_iSize;
        // allocating seperate memory for new object for which constructor is called
        this->m_iptrArr = new int[otherObj.m_iSize];

        for (int i = 0; i < m_iSize; i++)
        {
            this->m_iptrArr[i] = otherObj.m_iptrArr[i];
        }

        cout << "Copy constructor size : " << otherObj.m_iSize << endl;
    }

    // 2) Copy Assignment operator
    TestOp &operator=(const TestOp &otherObj)
    {
        if (this != &otherObj)
        {
            delete[] this->m_iptrArr;
            m_iptrArr = nullptr;

            this->m_iSize = otherObj.m_iSize;
            this->m_iptrArr = new int[otherObj.m_iSize];

            for (int i = 0; i < m_iSize; i++)
            {
                this->m_iptrArr[i] = otherObj.m_iptrArr[i];
            }
        }
        cout << "Copy Assignment operator " << endl;
        return *this;
    }

    // 3) Destructor
    ~TestOp()
    {
        // Deallocating resorces
        if (m_iptrArr)
        {
            delete[] m_iptrArr;
            m_iptrArr = nullptr;
        }

        cout << "Destructor " << endl;
    }

    // 4) move constructor
    // taking rValue Reference object as input
    // noexcept : This tells the STL containers: it's safe to move this object without risk of exceptions

    TestOp(TestOp &&otherObj) noexcept
    {
        // transfered the owernership
        m_iptrArr = otherObj.m_iptrArr;
        m_iSize = otherObj.m_iSize;

        // Leave the resources
        otherObj.m_iSize = 0;
        otherObj.m_iptrArr = nullptr;

        cout << "Move constructor \n";
    }

    // 5) move assignment operator
    TestOp &operator=(TestOp &&otherObj) noexcept
    {
        if (this != &otherObj)
        {
            delete m_iptrArr;
            m_iptrArr = nullptr;

            // Transfering owernship
            m_iptrArr = otherObj.m_iptrArr;
            m_iSize = otherObj.m_iSize;

            // Leave the resource
            otherObj.m_iptrArr = nullptr;
            otherObj.m_iSize = 0;
        }
        cout << "Move Assignment\n";

        return *this;
    }
    void printArray()
    {
        for (int i = 0; i < m_iSize; i++)
            cout << m_iptrArr[i] << " ";

        cout << endl;
    }
};

int main()
{
    /*
        TestOp obj1(3);
        obj1.m_iptrArr[0] = 11;
        obj1.m_iptrArr[1] = 21;
        obj1.m_iptrArr[2] = 51;

        // it's construction using a copy.
        // So this calls your copy constructor, not the copy assignment operator.
        TestOp obj2 = obj1;

        TestOp obj3(obj1); // call copy constructor

        obj2.m_iptrArr[1] = 47;
        obj3.m_iptrArr[1] = 97;

        obj3 = obj2; // this is copy assignment

        /*
         To illustrate the effect of move constructor, we have to turn off the compiler optimization (only in case of temporary objects)
         So the compilation command looks like below:

         g++ test.cpp -o test -fno-elide-constructors

        TestOp obj4 = TestOp(6); // Temporary object creatd and assigned to obj4

        TestOp obj5 = move(obj4); // move() typecast the lVaue into rValue..

        cout << obj5.m_iSize << endl; // 6
        cout << obj4.m_iSize << endl; // 0  sice obj4 can't access the resouces after the transering owerning to obj5


        // Assignment operator overloaded function only calls when thee both side objects are alredy constructred

        obj4 = move(obj5);  // transering owernship from obj5 to obj4

        cout << obj5.m_iSize << endl; // 0 sice obj5 can't access the resouces after the transering owerning to obj4
        cout << obj4.m_iSize << endl; // 6
    */

    // Important uses of move constructor in containers..
    vector<TestOp> vect;
    vect.reserve(2); // allocating vector of size 2

    vect.push_back(TestOp(2));
    vect.push_back(TestOp(3));

    /*
        TestOp(2) — Temporary Object Creation
        1) temporary object is created using the constructor: TestOp(int size).

        2) push_back(TestOp(2))
            The temporary is an rvalue. So, if TestOp has a move constructor, it is moved into the vector.

        If move constructor doesn't exist but copy constructor exists, it will fall back to copy.

        Modern compilers use move constructor here if available — much faster than copying.
        */

    vect.push_back(TestOp(3));

    // if we inserted extra elment into containers than size, then it will increse it's capacity and copied all previous
    // data into new resized vector... but if we had move constructor then move will happens. and it is more efficient than copy.

    return 0;
}