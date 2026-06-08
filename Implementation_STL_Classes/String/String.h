#pragma once
#include <cstring>
#include <iostream>
#include <string>

class String
{
private:
    int m_size{};
    int m_capacity{};
    char *m_data{nullptr};

public:
    String() : m_size(0), m_capacity(1), m_data(new char[1]{'\0'}) {};
    ~String();
    String(int n, const char &ch);
    String(const char *other); // C-string constructor
    String(const String &other);
    String(String &&other); // move constructor

    // Assignement operator opverloads
    String &operator=(const String &other);
    String &operator=(String &&other);

    // Element acces
    char &operator[](int indx) { return m_data[indx]; }
    const char &operator[](int indx) const { return m_data[indx]; }

    // Modifiers
    String operator+(const String &other) const;
    String operator+(const char *other) const;
    String &operator+=(const String &other);
    String &operator+=(const char *other);

    // Comparison
    bool operator==(const String &other) const;

    // Input output Stream
    friend std::ostream &operator<<(std::ostream &out, const String &obj);
    friend std::istream &operator>>(std::istream &in, String &obj);

    // Methods
    int length() const { return m_size; }
    int size() const { return m_size; }
    int capacity() const { return m_capacity; }
    void push_back(const char &ch);
    void pop_back();
    void clear();
    void resize(int n);
    void reserve(int n);
};

String::~String()
{
    delete[] m_data;
    m_size = m_capacity = 0;
}
String::String(int n, const char &ch)
{
    if (n < 0)
        n = 0;

    reserve(n);
    m_size = n;
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = ch;
    }
    m_data[m_size] = '\0';
}
String::String(const char *other)
{
    if (!other)
    {
        reserve(1);
        m_size = 0;
        m_data[0] = '\0';
        return;
    }

    int len = strlen(other);
    reserve(len);
    m_size = len;
    for (int i = 0; i < len; i++)
    {
        m_data[i] = other[i];
    }
    m_data[m_size] = '\0';
}

String::String(const String &other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new char[m_capacity + 1]{};

    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }
    m_data[m_size] = '\0';
}

String::String(String &&other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;

    other.m_size = 0;
    other.m_capacity = 1;
    other.m_data = new char[1]{'\0'};
}

// Memory Mangament
void String::resize(int newSize)
{
    if (newSize < 0)
        return;

    if (newSize <= m_capacity)
    {
        if (!m_data)
            reserve(1);

        m_size = newSize;
        m_data[m_size] = '\0';
        return;
    }

    char *temp = new char[newSize + 1]{};
    for (int i = 0; i < m_size; i++)
    {
        temp[i] = m_data[i];
    }

    delete[] m_data;
    m_data = temp;
    m_size = m_capacity = newSize;
    m_data[m_size] = '\0';
}
void String::reserve(int newCap)
{
    if (newCap <= m_capacity && m_data)
    {
        return;
    }

    if (newCap < 1)
        newCap = 1;

    char *temp = new char[newCap + 1]{};
    for (int i = 0; i < m_size; i++)
    {
        temp[i] = m_data[i];
    }

    delete[] m_data;
    m_data = temp;
    m_capacity = newCap;
}

// Overloaded Operator
String &String::operator=(const String &other)
{
    if (this == &other)
        return *this;

    delete[] m_data;
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data = new char[m_capacity + 1]{};

    if (m_size > 0)
    {
        memcpy(m_data, other.m_data, m_size);
    }
    m_data[m_size] = '\0';

    return *this;
}
String &String::operator=(String &&ohter)
{
    if (this == &ohter)
        return *this;

    delete[] m_data;
    m_capacity = ohter.m_capacity;
    m_size = ohter.m_size;
    m_data = ohter.m_data;

    ohter.m_capacity = 1;
    ohter.m_size = 0;
    ohter.m_data = new char[1]{'\0'};

    return *this;
}

String &String::operator+=(const String &other)
{
    *this = (*this + other);
    return *this;
}

String String::operator+(const String &other) const
{
    String result;
    result.reserve(m_size + other.m_size);
    result.m_size = m_size + other.m_size;

    // copy left part
    for (int i = 0; i < m_size; i++)
    {
        result.m_data[i] = m_data[i];
    }

    // append right string
    for (int i = 0; i < other.m_size; i++)
    {
        result.m_data[m_size + i] = other.m_data[i];
    }

    result.m_data[result.m_size] = '\0';
    return result;
}
String &String::operator+=(const char *other)
{
    *this = (*this + other);
    return *this;
}

String String::operator+(const char *other) const
{
    if (!other)
        return *this;

    int len = strlen(other);
    String result;
    result.reserve(m_size + len);
    result.m_size = m_size + len;

    // copy left part
    for (int i = 0; i < m_size; i++)
    {
        result.m_data[i] = m_data[i];
    }

    // append right string
    for (int i = 0; i < len; i++)
    {
        result.m_data[m_size + i] = other[i];
    }

    result.m_data[result.m_size] = '\0';
    return result;
}
bool String::operator==(const String &other) const
{
    if (m_size != other.m_size)
        return false;

    for (int i = 0; i < m_size; i++)
    {
        if (m_data[i] != other.m_data[i])
            return false;
    }

    return true;
}

std::ostream &operator<<(std::ostream &out, const String &obj)
{
    out << obj.m_data;
    return out;
}
std::istream &operator>>(std::istream &in, String &obj)
{
    std::string temp;
    in >> temp;
    obj = temp.c_str();
    return in;
}

// Modifieres methods
void String::push_back(const char &ch)
{
    if (m_size == m_capacity)
    {
        int newCap = m_capacity == 0 ? 1 : m_capacity * 2;
        reserve(newCap);
    }

    m_data[m_size] = ch;
    m_size++;
    m_data[m_size] = '\0';
}

void String::pop_back()
{
    if (m_size == 0)
        return;

    m_size--;
    m_data[m_size] = '\0';
}

void String::clear()
{
    m_size = 0;
    if (m_data)
        m_data[0] = '\0';
}