#include <bits/stdc++.h>
using namespace std;

//It allows an object to change its behavior when its internal state changes.

// forward declaration..
class TraficLight;

// Abstract State
class State
{
public:
    virtual void update(TraficLight *ptr) = 0;
};

// Context
class TraficLight
{
    State *m_ptrState;

public:
    TraficLight(State *ptrState) : m_ptrState(ptrState) {}

    void setState(State *ptrState)
    {
        if (m_ptrState)
            delete m_ptrState;

        m_ptrState = ptrState;
    }

    void change()
    {
        m_ptrState->update(this);
    }
};

// Concrete State
class YellowState : public State
{
public:
    void update(TraficLight *ptr) override;
};

class GreenState : public State
{
public:
    void update(TraficLight *ptr) override;
};

class RedState : public State
{
public:
    void update(TraficLight *ptr) override;
};

void YellowState::update(TraficLight *ptr)
{
    cout << "Yellow -> slow down || Next-> Red \n";
    ptr->setState(new RedState());
}

void GreenState::update(TraficLight *ptr)
{
    cout << "Green -> Go || Next-> Yellow \n";
    ptr->setState(new YellowState());
}

void RedState::update(TraficLight *ptr)
{
    cout << "Red -> Stop || Next-> Green \n";
    ptr->setState(new GreenState());
}

int main()
{
    TraficLight light(new RedState());

    light.change();
    light.change();
    light.change();
    light.change();

    return 0;
}