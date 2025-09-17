#include <bits/stdc++.h>
using namespace std;

// Open closed Principle
/*
Definition: Software entities (classes, modules, functions) should be open for extension, but closed for modification.
What does it actually mean?
    • Open for extension → you can add new functionality
    • Closed for modification → you should not change existing tested code to do it
Goal: Add new features without breaking existing logic

*/

// Violated the OCP
//  Every time a new method (like UPI, Crypto Pay) is added, you have to:

// Modify this class
// Risk of breaking existing code
// Add more if-else
// It is neither scalable nor maintainable.
class ProceesPayment
{
    void processPayment(string paymentMethod)
    {
        if (paymentMethod == "CreditCard")
        {
            //...
        }
        else if (paymentMethod == "DebitCard")
        {
            //...
        }
    }
};

// Following the OCP Principle
// PaymentProcessor class is open for adding new features, but closed for modification

// Interface (Abstract class)
class PaymentStrategy
{
public:
    virtual void pay() = 0; // pure virtual function
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategy 1
class CreditCardPayment : public PaymentStrategy
{
public:
    void pay() override
    {
        cout << "Credit card payment processed" << endl;
    }
};

// Concrete Strategy 2
class UPIPayment : public PaymentStrategy
{
public:
    void pay() override
    {
        cout << "UPI payment processed" << endl;
    }
};

// Context Class
class PaymentProcessor
{
private:
    PaymentStrategy *m_ptrPaymentStrategy;

public:
    PaymentProcessor(PaymentStrategy *ptrPaymentStrategy)
        : m_ptrPaymentStrategy(ptrPaymentStrategy) {}

    void process()
    {
        m_ptrPaymentStrategy->pay();
    }
};
int main()
{

    // Usages
    PaymentProcessor *ptrObjPayment = new PaymentProcessor(new UPIPayment());
    ptrObjPayment->process();

    delete ptrObjPayment;
    ptrObjPayment = nullptr;
    return 0;
}