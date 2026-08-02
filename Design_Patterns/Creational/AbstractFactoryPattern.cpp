#include <bits/stdc++.h>
using namespace std;

/*
What We Really Need
A way to group related components by family (all Windows components together, all macOS components together)
Encapsulated creation logic so platform checks happen in exactly one place
Polymorphic products so the client works with Button and Checkbox interfaces, not concrete classes
Structural guarantees that mixing families is impossible, not just discouraged
This is exactly what the Abstract Factory pattern provides.


What is Abstract Factory
The Abstract Factory Pattern provides an interface for creating families of related or dependent objects without specifying their concrete classes.

The key word is families. Factory Method deals with creating one product at a time. Abstract Factory deals with creating multiple products that must work together. A GUI factory does not just create buttons. It creates buttons, checkboxes, text fields, and menus that all share the same visual style.
*/

//Abstract product
class Button
{
public:
    virtual void onClick() = 0;
    virtual ~Button() = default;
};

//Abstract product
class CheckBox
{
public:
    virtual void onSelect() = 0;
    virtual ~CheckBox() = default;
};

//Concreate Product
class WindowsButton : public Button
{
public:
    void onClick() override
    {
        cout << "Windows button clicked" << endl;
    }
};

//Concreate Product
class LinuxButton : public Button
{
public:
    void onClick() override
    {
        cout << "Linux button clicked" << endl;
    }
};

//Concreate Product
class WindowsCheckBox : public CheckBox
{
public:
    void onSelect() override
    {
        cout << "Window CheckBox selected" << endl;
    }
};

//Concreate Product
class LinuxCheckBox : public CheckBox
{
public:
    void onSelect() override
    {
        cout << "Linux CheckBox selected" << endl;
    }
};

// Abstract Factory
class GUIFactory
{
public:
    virtual Button *createButton() = 0;
    virtual CheckBox *createCheckBox() = 0;
};

//concreate factory
class WindowsFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new WindowsButton();
    }
    CheckBox *createCheckBox() override
    {
        return new WindowsCheckBox();
    }
};


//concreate factory
class LinuxFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new LinuxButton();
    }
    CheckBox *createCheckBox() override
    {
        return new LinuxCheckBox();
    }
};

int main()
{
    GUIFactory *factory = new WindowsFactory();
    factory->createButton()->onClick();
    factory->createCheckBox()->onSelect();

    GUIFactory *factory2 = new LinuxFactory();
    factory2->createButton()->onClick();
    factory2->createCheckBox()->onSelect();

    delete factory;
    delete factory2;

    return 0;
}