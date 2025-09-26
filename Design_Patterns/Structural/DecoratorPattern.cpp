#include <bits/stdc++.h>
using namespace std;

// The Decorator pattern lets you attach new behaviors or responsibilities to an object dynamically.

// Component
class Coffe
{
public:
    virtual string getDescription() = 0;
    virtual int getCost() = 0;
    virtual ~Coffe() = default;
};

//Concreate componetn
class BaseCoffee : public Coffe
{
public:
    string getDescription() override
    {
        return "Simple Coffe ";
    }

    int getCost() override
    {
        return 10;
    }
};

//Decorator
class CoffeDecorator : public Coffe
{
public:
    Coffe *ptrObj; // It wraps another coffe object
    CoffeDecorator(Coffe *ptr) : ptrObj(ptr) {}

    ~CoffeDecorator()
    {
        delete ptrObj;
        ptrObj = nullptr;
    }
};

//Concreat Decorator
class MilkDecorator : public CoffeDecorator
{
public:
    MilkDecorator(Coffe *ptr) : CoffeDecorator(ptr) {}

    string getDescription() override
    {
        return ptrObj->getDescription() + " + Milk ";
    }

    int getCost() override
    {
        return ptrObj->getCost() + 15;
    }
};

class ChocoDecorator : public CoffeDecorator
{
public:
    ChocoDecorator(Coffe *ptr) : CoffeDecorator(ptr) {}

    string getDescription() override
    {
        return ptrObj->getDescription() + " + Chocolocate ";
    }

    int getCost() override
    {
        return ptrObj->getCost() + 20;
    }
};

int main()
{
    Coffe *ptrObjCoffee = new BaseCoffee();

    string display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
    cout << display << endl;

    ptrObjCoffee = new MilkDecorator(ptrObjCoffee);
    display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
    cout << display << endl;

    ptrObjCoffee = new ChocoDecorator(ptrObjCoffee);
    display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
    cout << display << endl;

    //Another way to add decorators in Base Coffee...
    Coffe *specialCofee = new ChocoDecorator(new BaseCoffee());
    cout << specialCofee->getDescription() << " " << specialCofee->getCost();

    delete ptrObjCoffee;
    ptrObjCoffee = nullptr;

    delete specialCofee;
    specialCofee = nullptr;

    return 0;
}