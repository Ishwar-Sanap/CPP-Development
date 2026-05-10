#pragma once

#include <iostream>
template <typename T>
class Vector
{
private:
    int m_size{};
    int m_capacity{};
    T *m_data{nullptr};

public:
    // Constructors & Destructor
    Vector();
    Vector(int n, const T &val = T{});
    Vector(const Vector<T> &other);       // copy
    Vector(Vector<T> &&other) noexcept;   // move
    Vector(std::initializer_list<T> lst); // Parameterized constructor for Initializer list
    ~Vector();

    // Assignment Operator overloads
    Vector &operator=(const Vector<T> &other);     //  copy
    Vector &operator=(Vector<T> &&other) noexcept; //  move

    // Memory
    void reserve(int capcity);
    void resize(int size);
    void clear();

    // Element access
    T &operator[](int indx); // returning reference value at that index
    T &at(int indx);
    T &front();
    T &back();

    // Methods
    void push_back(const T &val);
    void pop_back();
    int size();
    int capacity();

    // ***** Optional *******
    // Implementing the Iterator Class: Iterator is nothing but pointer points to the m_data at perticular position..
    // Iterator class
    class Iterator
    {
    private:
        T *m_ptr{nullptr};

    public:
        // Constructor
        Iterator(T *ptr = nullptr) : m_ptr(ptr) {}

        // Dereference operators
        T &operator*() { return *m_ptr; }
        T *operator->() { return m_ptr; }

        // Increment/Decrement
        Iterator &operator++() // pre increment
        {
            ++m_ptr;
            return *this;
        }
        Iterator operator++(int) //post increment
        {
            Iterator temp = *this;
            ++m_ptr;
            return temp;
        }

        Iterator &operator--()
        {
            --m_ptr;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator temp = *this;
            --m_ptr;
            return temp;
        }

        // Comparison operators
        bool operator==(const Iterator &other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const Iterator &other) const { return m_ptr != other.m_ptr; }

        // Random access operators
        T &operator[](int index) { return *(m_ptr + index); }
        Iterator operator+(int offset) { return Iterator(m_ptr + offset); }
        Iterator operator-(int offset) { return Iterator(m_ptr - offset); }
        Iterator &operator+=(int offset)
        {
            m_ptr += offset;
            return *this;
        }
        Iterator &operator-=(int offset)
        {
            m_ptr -= offset;
            return *this;
        }
    };
    // Iterator methods
    Iterator begin() { return Iterator(m_data); }
    Iterator end() { return Iterator(m_data + m_size); }
};
// Default constructor
template <typename T>
Vector<T>::Vector()
{
    m_size = m_capacity = 0;
    m_data = nullptr;
}

// Parameterized constructor
template <typename T>
Vector<T>::Vector(int n, const T &val)
{
    m_capacity = n;
    m_data = new T[n]{val};
}

// Parameterized constructor for Initializer list
template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst) : Vector(lst.size())
{
    for (auto &ele : lst)
    {
        push_back(ele);
    }
}

// Copy Costructor
template <typename T>
Vector<T>::Vector(const Vector<T> &other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }
}
// Move constructor
template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept
{
    // moving owenership of resources from other object to new object
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

// Destructor
template <typename T>
Vector<T>::~Vector()
{
    m_size = 0;
    m_capacity = 0;
    delete[] m_data;
    m_data = nullptr;
}
// Copy Assignment operator
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
    std::cout << "Copy assignment " << std::endl;
    if (this == &other)
        return *this;

    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];

    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

// move assignment operator
template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    if (this == &other)
        return *this;

    delete[] m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;

    return *this;
}

template <typename T>
void Vector<T>::push_back(const T &val)
{
    if (m_size == m_capacity)
    {
        int newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
        reserve(newCapacity);
    }

    m_data[m_size] = val;
    m_size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size <= 0)
        return;

    m_size--;
}

template <typename T>
int Vector<T>::size()
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity()
{
    return m_capacity;
}

// Element Access
template <typename T>
T &Vector<T>::front()
{
    return m_data[0];
}

template <typename T>
T &Vector<T>::back()
{
    return m_data[m_size - 1];
}

template <typename T>
T &Vector<T>::at(int indx)
{
    if (indx >= m_size || indx < 0)
        throw std::out_of_range("Vector element access out of range");

    return m_data[indx];
}

template <typename T>
T &Vector<T>::operator[](int indx)
{
    return m_data[indx];
}

template <typename T>
void Vector<T>::reserve(int newCapcity)
{
    if (newCapcity <= m_capacity)
        return;

    T *newData = new T[newCapcity]{};
    for (int i = 0; i < m_size; i++)
    {
        newData[i] = std::move(m_data[i]);
    }

    delete[] m_data;
    m_data = newData;

    m_capacity = newCapcity;
}
template <typename T>
void Vector<T>::resize(int newSize)
{
    if (newSize <= m_size || newSize <= m_capacity)
    {
        m_size = newSize;
    }
    else
    {
        T *newData = new T[newSize]{};
        for (int i = 0; i < m_size; i++)
        {
            newData[i] = std::move(m_data[i]);
        }

        delete[] m_data;
        m_data = newData;

        m_size = newSize;
        m_capacity = newSize;
    }
}
template <typename T>
void Vector<T>::clear()
{
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = T{}; // assign with default value
    }
    m_size = 0;
}