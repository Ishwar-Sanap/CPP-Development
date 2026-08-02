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

// Concreate componetn
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

// Decorator
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

// Concreat Decorator
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

// int main()
// {
//     Coffe *ptrObjCoffee = new BaseCoffee();

//     string display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
//     cout << display << endl;

//     ptrObjCoffee = new MilkDecorator(ptrObjCoffee);
//     display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
//     cout << display << endl;

//     ptrObjCoffee = new ChocoDecorator(ptrObjCoffee);
//     display = ptrObjCoffee->getDescription() + to_string(ptrObjCoffee->getCost());
//     cout << display << endl;

//     // Another way to add decorators in Base Coffee...
//     Coffe *specialCofee = new ChocoDecorator(new BaseCoffee());
//     cout << specialCofee->getDescription() << " " << specialCofee->getCost();

//     delete ptrObjCoffee;
//     ptrObjCoffee = nullptr;

//     delete specialCofee;
//     specialCofee = nullptr;

//     return 0;
// }

// Example2
// Simple Text viewer

class TextViewer
{
public:
    virtual void render() = 0;
    virtual ~TextViewer() = default;
};

// This is the basic object we want to decorate.
class PlainText : public TextViewer
{
    string text;

public:
    PlainText(const string &text) : text(text) {}
    void render() override
    {
        cout << text;
    }
};

class TextDecorator : public TextViewer
{
protected:
    TextViewer *inner;

public:
    TextDecorator(TextViewer *inner) : inner(inner) {}

    ~TextDecorator()
    {
        // This is not always safe to directly delete memory here
        //  since, inner poiner can points to memory which is allocated on stack not heap,
        // so we can't delete stack allocated memory using delete, to handle this we must add flag in class member to check allocation type
        //  delete inner;
        //  inner = nullptr;
    }
};

class BoldTextDecorator : public TextDecorator
{
public:
    BoldTextDecorator(TextViewer *inner) : TextDecorator(inner) {}

    void render() override
    {
        cout << "<b>";
        inner->render();
        cout << "</b>";
    }
};
class ItalicTextDecorator : public TextDecorator
{
public:
    ItalicTextDecorator(TextViewer *inner) : TextDecorator(inner) {}

    void render() override
    {
        cout << "<i>";
        inner->render();
        cout << "</i>";
    }
};

int main()
{
    PlainText text("Hello world");
    // text.render();

    BoldTextDecorator btext(&text);
    // btext.render();

    ItalicTextDecorator itext(&btext);
    itext.render();

    cout << endl;

    TextViewer *ptr = new ItalicTextDecorator(new PlainText("Decorator Pattern"));
    ptr->render();
    cout << endl;

    delete ptr;

    return 0;
}