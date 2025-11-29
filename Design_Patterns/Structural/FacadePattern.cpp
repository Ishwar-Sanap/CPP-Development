#include <bits/stdc++.h>
using namespace std;

/*
        - Imagine you’re working with a complex system (lots of classes, methods, dependencies).
            • To perform one simple task, the client has to deal with many classes.
            • This makes the code messy, hard to read, and harder to maintain.
The Facade provides a single unified interface that hides all the complexity.

         • Instead of calling 5 different classes, the client just calls one method on the Facade
        - The Facade delegates internally to the right subsystems.

*/

class Grinder
{
public:
    void grindSeeds() { cout << "Grinding seeds" << endl; }
};
class Brewer
{
public:
    void brewCoffee() { cout << "Brewing cofee" << endl; }
};

class MilkFother
{
public:
    void addMilk() { cout << "Adding milk.." << endl; }
};

class SugarDispenser
{
public:
    void addSugar() { cout << "Adding sugar...\n"; }
};

class CoffeeMachinFacade
{
    Grinder *m_ptrGR;
    MilkFother *m_ptrMF;
    SugarDispenser *m_ptrSD;
    Brewer *m_ptrBrewer;
public:
    CoffeeMachinFacade(Grinder *g, Brewer *br, MilkFother *mf, SugarDispenser *sd) : m_ptrGR(g), m_ptrMF(mf),
                                                                                     m_ptrSD(sd), m_ptrBrewer(br)
    {
    }

    void makeSimpleCoffe()
    {
        m_ptrGR->grindSeeds();
        m_ptrBrewer->brewCoffee();
        cout << "Simple coffee is ready \n";
    }

    void makeCofeeWithMilk()
    {
        m_ptrGR->grindSeeds();
        m_ptrBrewer->brewCoffee();
        m_ptrMF->addMilk();

        cout << "Coffe with milk is ready\n";
    }

    void makeCoffeWithMilkAndSugar()
    {
        m_ptrGR->grindSeeds();
        m_ptrBrewer->brewCoffee();
        m_ptrMF->addMilk();
        m_ptrSD->addSugar();
        cout << "Coffe with milk and sugar is ready\n";
    }

    ~CoffeeMachinFacade()
    {
        m_ptrBrewer = nullptr;
        m_ptrGR = nullptr;
        m_ptrSD = nullptr;
        m_ptrMF = nullptr;
    }
};

int main()
{
    Grinder gr;
    Brewer br;
    SugarDispenser sd;
    MilkFother mf;

    CoffeeMachinFacade *ptrCofeeFacade = new CoffeeMachinFacade(&gr, &br, &mf, &sd);

    ptrCofeeFacade->makeSimpleCoffe();
    
    cout<<" ------------------------------------\n";

    ptrCofeeFacade->makeCoffeWithMilkAndSugar();

    delete ptrCofeeFacade;
    ptrCofeeFacade = nullptr;

    return 0;
}