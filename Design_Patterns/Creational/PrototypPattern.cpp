#include <bits/stdc++.h>
using namespace std;

// Prototype pattern lets you clone existing objects
// (deep or shallow copy), instead of constructing new ones.

// Prototype
class Employee
{
public:
    virtual void getLanguage() = 0;
    virtual Employee *clone() = 0;
    virtual ~Employee() = default;
};

// Concreate prototype
class JavaDev : public Employee
{
    string lang;

public:
    JavaDev(string str) : lang(str) {}

    Employee *clone()
    {
        // creating the deep copy
        return new JavaDev(this->lang);
    }
    void getLanguage() override
    {
        cout << "Lang of Java dev : " << lang << endl;
    }
};

class WebDev : public Employee
{
    string lang;

public:
    WebDev(string str) : lang(str) {}
    Employee *clone()
    {
        // creating the deep copy
        return new WebDev(this->lang);
    }
    void getLanguage() override
    {
        cout << "Lang of Web dev : " << lang << endl;
    }
};

// client
int main()
{
    Employee *ptrJava1 = new JavaDev("java");
    ptrJava1->getLanguage();

    Employee *ptrJava2 = ptrJava1->clone();
    ptrJava2->getLanguage();

    Employee *ptrWeb1 = new JavaDev("java scripts");
    ptrWeb1->getLanguage();

    Employee *ptrWeb2 = ptrJava1->clone();
    ptrWeb1->getLanguage();

    delete ptrJava1;
    delete ptrJava2;
    delete ptrWeb1;
    delete ptrWeb2;
    return 0;
}