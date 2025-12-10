#include <iostream>
using namespace std;

template <class T>
class Vector
{
private:
    T *m_ptrTData;
    int m_iCapacity; // how much space is taken for vector
    int m_iSize;     // number of elements in vector

public:
    // default constructor
    Vector() : m_ptrTData(nullptr), m_iCapacity(0), m_iSize(0) {}

    ~Vector()
    {
        delete[] m_ptrTData;
        m_iCapacity = 0;
        m_iSize = 0;
    }

    // parameterised constructor
    Vector(int size) : m_ptrTData(new T[size]), m_iCapacity(size), m_iSize(0) {}

    // initializer list parameterised constructor
    Vector(std::initializer_list<T> lst) : Vector(lst.size())
    {
        // copying m_ptrTData from initializer list into m_ptrTData
        for (auto &it : lst)
        {
            push_back(it);
        }
    }

    // Copy constructor
    Vector(const Vector &otherObj)
    {
        cout << "callled cpy constructr \n";
        m_iCapacity = otherObj.m_iCapacity;
        m_iSize = otherObj.m_iSize;

        m_ptrTData = new T[m_iCapacity];

        for (int i = 0; i < otherObj.m_iSize; i++)
        {
            m_ptrTData[i] = otherObj.m_ptrTData[i];
        }
    }

    // copy assignement operator
    Vector &operator=(const Vector &otherObj)
    {
        cout << "callled cpy assignment \n";
        if (this != &otherObj)
        {
            m_iCapacity = otherObj.m_iCapacity;
            m_iSize = otherObj.m_iSize;

            T *temp = new T[m_iCapacity];

            for (int i = 0; i < m_iSize; i++)
            {
                temp[i] = otherObj.m_ptrTData[i];
            }

            delete[] m_ptrTData;
            m_ptrTData = temp;
        }

        return *this;
    }

    // move copy constructor
    Vector(Vector &&otherObj)
    {
        cout << "callled move constructr \n";

        m_iCapacity = otherObj.m_iCapacity;
        m_iSize = otherObj.m_iSize;
        m_ptrTData = otherObj.m_ptrTData;

        // moving owenership from other object
        otherObj.m_ptrTData = nullptr;
        otherObj.m_iSize = 0;
        otherObj.m_iCapacity = 0;
    }

    // move assignment operator
    Vector &operator=(Vector &&otherObj)
    {
        cout << "callled move assignment \n";

        if (this != &otherObj)
        {

            delete[] m_ptrTData;
            m_ptrTData = otherObj.m_ptrTData;
            m_iCapacity = otherObj.m_iCapacity;
            m_iSize = otherObj.m_iSize;

            // moving owenership from other object
            otherObj.m_ptrTData = nullptr;
            otherObj.m_iSize = 0;
            otherObj.m_iCapacity = 0;
        }

        return *this;
    }

    // Overloading the required operator to support accessing element
    T &operator[](int indx)
    {
        return m_ptrTData[indx];
    }

    void push_back(T ele)
    {
        if (m_iCapacity <= m_iSize)
        {
            reserve(m_iCapacity == 0 ? 1 : m_iCapacity * 2);
        }
        m_ptrTData[m_iSize] = ele;
        m_iSize++;
    }

    void reserve(int newCap)
    {
        if (newCap > m_iCapacity)
        {
            // creating new array
            T *temp = new T[newCap];

            // copy all previous elements into new array and delete older memory
            for (int i = 0; i < m_iSize; i++)
            {
                temp[i] = std::move(m_ptrTData[i]);
            }

            delete[] m_ptrTData;
            m_ptrTData = temp;

            m_iCapacity = newCap;
        }
    }

    void resize(int newSize)
    {
        if (newSize > m_iSize)
        {
            // creating new array
            T *temp = new T[newSize]{}; // universal default initialization {}
            for (int i = 0; i < m_iSize; i++)
            {
                // copy all previous elements
                temp[i] = m_ptrTData[i];
            }
            delete[] m_ptrTData;
            m_ptrTData = temp;
            m_iSize = newSize;
            m_iCapacity = newSize;
        }
        else
        {
            m_iSize = newSize;
        }
    }

    void pop_back()
    {
        if (m_iSize > 0)
        {
            m_iSize--;
        }
    }

    int size() { return m_iSize; }

    int capacity() { return m_iCapacity; }

    void clear()
    {
        for (int i = 0; i < m_iSize; i++)
        {
            m_ptrTData[i] = T{}; // assigning with default value.
        }

        m_iSize = 0;
    }

    // ***** Optional *******
    // Implementing the Iterator Class: Iterator is nothing but pointer points to the m_ptrTData at perticular position..

    class iterator
    {
    private:
        T *m_ptr;

    public:
        iterator(T *ptr) : m_ptr(ptr) {};

        // overload the required operator..

        T &operator*() { return *m_ptr; }
        T *operator->() { return m_ptr; }

        // increment

        iterator &operator++() // pre increment
        {
            ++m_ptr;
            return *this;
        }
        iterator &operator++(int) // post increment
        {
            iterator temp = *this;
            ++m_ptr;
            return temp;
        }

        // decrement 
        iterator &operator--()
        {
            --m_ptr;
            return *this;
        }

        // comparison
        bool operator==(const iterator &other) { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator &other) { return m_ptr != other.m_ptr; }
    };

    iterator begin() { return iterator(m_ptrTData); }
    iterator end() { return iterator(m_ptrTData + m_iSize); }
};

void printArr(Vector<int> &arr)
{
    // for (int i = 0; i < arr.size(); i++)
    // {
    //     cout << arr[i] << " ";
    // }

    // for (auto it = arr.begin(); it != arr.end(); ++it)
    // {
    //     cout << *it << " ";
    // }

    for (auto ele : arr)
    {
        cout << ele << " ";
    }

    cout << endl;
}

int main()
{

    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    v1.pop_back();

    printArr(v1);

    cout << "cap : " << v1.capacity() << endl;
    cout << "size : " << v1.size() << endl;

    Vector<int> v2 = {3, 5, 7, 9};
    v2.push_back(11);
    v2.push_back(15);

    v2[3] = 333;

    printArr(v2);

    Vector<int> v3 = v1; // copy construcotr

    v1 = v2; // copy assignment operator

    Vector<int> v4 = std::move(v2); // move constructor

    v1 = std::move(v4); // move assignment

    v1.resize(10);

    printArr(v1);
    v1.clear();

    printArr(v1);

    return 0;
}