#include <bits/stdc++.h>
using namespace std;

// Abstract class
class Employee
{
public:
    Employee() {};
    virtual ~Employee() {};
    virtual int salary() = 0;
};

class WebDev : public Employee
{
    int salary()
    {
        cout << "salary of web developer " << endl;
        return 50000;
    }
};

class JavaDev : public Employee
{
    int salary()
    {
        cout << "salary of Java developer " << endl;
        return 150000;
    }
};

class EmployeeFactory
{
public:
    static Employee *getEmployeeObj(string type)
    {
        if (type == "Web Dev")
            return new WebDev();
        else if (type == "Java Dev")
            return new JavaDev();
        else
            return nullptr;
    }
};


int main()
{
    //Client code
    Employee *e1 = EmployeeFactory::getEmployeeObj("Web Dev");

    Employee *e2 = EmployeeFactory::getEmployeeObj("Java Dev");

    cout << e1->salary() << endl;

    cout << e2->salary() << endl;

    delete e1;
    e1 = nullptr;

    delete e2;
    e2 = nullptr;

    return 0;
}