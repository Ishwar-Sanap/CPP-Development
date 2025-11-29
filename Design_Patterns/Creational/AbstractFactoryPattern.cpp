#include <bits/stdc++.h>
using namespace std;

// Abstract product 1
class Employee
{
public:
    Employee() {};
    virtual ~Employee() {};
    virtual int salary() = 0;
};

// Abstract product 2
class Tool
{
public:
    virtual ~Tool() = default;
    virtual void toolUsed() = 0;
};

// Concreate products
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

class VsCode : public Tool
{
    void toolUsed()
    {
        cout << "Using VsCode " << endl;
    }
};
class Ecliplse : public Tool
{
    void toolUsed()
    {
        cout << "Using Ecliplse IDE " << endl;
    }
};

//Abstract Factory → Declares creation methods for families.
class EmployeeAbstractFactory
{
public:
    virtual ~EmployeeAbstractFactory() = default;
    virtual Employee *getEmployeeObj() = 0;
    virtual Tool *getToolUsedObj() = 0;
};

//Concrete Factories → Implement creation methods for a specific family.
class WebDevFactory : public EmployeeAbstractFactory
{
public:
    Employee *getEmployeeObj() { return new WebDev(); }
    Tool *getToolUsedObj() { return new VsCode(); }
};
class JavaDevFactory : public EmployeeAbstractFactory
{
public:
    Employee *getEmployeeObj() { return new JavaDev(); }
    Tool *getToolUsedObj() { return new Ecliplse(); }
};

int main()
{
    // Client code
    string type = "Java Dev";

    EmployeeAbstractFactory *ptObjFactory = nullptr;
    if (type == "Java Dev")
    {
        ptObjFactory = new JavaDevFactory();
    }

    Employee *e1 = ptObjFactory->getEmployeeObj();
    Tool *t1 = ptObjFactory->getToolUsedObj();

    cout << e1->salary() << endl;

    t1->toolUsed();

    delete e1;
    e1 = nullptr;

    delete t1;
    t1 = nullptr;

    return 0;
}