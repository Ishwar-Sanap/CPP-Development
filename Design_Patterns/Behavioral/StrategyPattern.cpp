#include <bits/stdc++.h>
using namespace std;

// Define a family of algorithms and choose one at runtime.

class PaymentStrategy
{
public:
    virtual void pay(int amout) = 0;
};

class UPIPayment : public PaymentStrategy
{
public:
    void pay(int amout) override
    {
        cout << amout << " paid using UPI \n";
    }
};
class CreditCardPayment : public PaymentStrategy
{
public:
    void pay(int amout) override
    {
        cout << amout << " paid using credit card \n";
    }
};

class ShoppingCart
{
    PaymentStrategy *m_ptrPaymentStrategy = nullptr;

public:
    void setPaymentStrtegy(PaymentStrategy *ptr)
    {
        m_ptrPaymentStrategy = ptr;
    }

    void makePayment(int amout)
    {
        m_ptrPaymentStrategy->pay(amout);
    }
};
int main()
{
    ShoppingCart obj;

    PaymentStrategy* ptrUPI = new UPIPayment();
    
    obj.setPaymentStrtegy(ptrUPI);
    obj.makePayment(100);
    
    PaymentStrategy* ptrCredit = new CreditCardPayment();

    obj.setPaymentStrtegy(ptrCredit);
    obj.makePayment(1000);

    //Insted of writing if/else or switch cases, we are strategically 
    //decides which payment should proceed
    delete ptrCredit;
    delete ptrUPI;

    return 0;
}