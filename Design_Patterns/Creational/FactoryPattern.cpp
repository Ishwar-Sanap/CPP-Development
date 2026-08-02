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

// Factory Pattern: one factory class creates objects.
//Simple approach, but it violates open close principle becuase every time when you want to add new type needs to add more if conditions

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

// Factory Method: object creation is delegated to subclasses.

class Animal {
public:
    virtual void speak() = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Bark\n";
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow\n";
    }
};

class AnimalFactory {
public:
    virtual unique_ptr<Animal> createAnimal() = 0;
    virtual ~AnimalFactory() = default;
};

class DogFactory : public AnimalFactory {
public:
    unique_ptr<Animal> createAnimal() override {
        return make_unique<Dog>();
    }
};

class CatFactory : public AnimalFactory {
public:
    unique_ptr<Animal> createAnimal() override {
        return make_unique<Cat>();
    }
};

// int main() {
//     DogFactory dogFactory;
//     auto dog = dogFactory.createAnimal();
//     dog->speak();

//     CatFactory catFactory;
//     auto cat = catFactory.createAnimal();
//     cat->speak();
// }