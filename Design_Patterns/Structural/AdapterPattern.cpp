#include <bits/stdc++.h>
using namespace std;

/*
The Adapter Design Pattern is a structural design pattern that allows incompatible interfaces to work together by converting the interface of one class into another that the client expects.

It’s particularly useful in situations where:

You’re integrating with a legacy system or a third-party library that doesn’t match your current interface.
You want to reuse existing functionality without modifying its source code.
You need to bridge the gap between new and old code, or between systems built with different interface designs.

*/

// Target Interface
class PaymentProcessor
{
public:
    virtual void processPayment(double amount, string currency) = 0;
    virtual bool isPaymentSuccessful() = 0;
    virtual string getTransactionId() = 0;
    virtual ~PaymentProcessor() {}
};

// Your team already has an internal payment processor that fits this interface perfectly:
class InHousePaymentProcessor : public PaymentProcessor
{
private:
    string transactionId;
    bool paymentSuccessful = false;

public:
    void processPayment(double amount, string currency) override
    {
        cout << "InHouseProcessor: Processing " << amount << " " << currency << endl;
        auto now = chrono::duration_cast<chrono::milliseconds>(
                       chrono::system_clock::now().time_since_epoch())
                       .count();
        transactionId = "TXN_" + to_string(now);
        paymentSuccessful = true;
        cout << "InHouseProcessor: Success. Txn ID: " << transactionId << endl;
    }

    bool isPaymentSuccessful() override
    {
        return paymentSuccessful;
    }

    string getTransactionId() override
    {
        return transactionId;
    }
};

// Your CheckoutService uses this interface and works beautifully with the in-house payment processor:
class CheckoutService
{
private:
    PaymentProcessor *paymentProcessor;

public:
    CheckoutService(PaymentProcessor *processor) : paymentProcessor(processor) {}

    void checkout(double amount, std::string currency)
    {
        std::cout << "Checkout: Processing order for $" << amount << " " << currency << std::endl;

        paymentProcessor->processPayment(amount, currency);

        if (paymentProcessor->isPaymentSuccessful())
        {
            std::cout << "Checkout: Order successful! Txn: "
                      << paymentProcessor->getTransactionId() << std::endl;
        }
        else
        {
            std::cout << "Checkout: Order failed." << std::endl;
        }
    }
};

// The Incompatible Legacy Gateway
// Here's what that legacy payment class looks like:
class LegacyGateway
{
private:
    long transactionReference = 0;
    bool paymentSuccessful = false;

public:
    void executeTransaction(double totalAmount, string currency)
    {
        cout << "LegacyGateway: Executing " << currency << " " << totalAmount << endl;
        transactionReference = chrono::duration_cast<chrono::nanoseconds>(
                                   chrono::system_clock::now().time_since_epoch())
                                   .count();
        paymentSuccessful = true;
        cout << "LegacyGateway: Done. Ref: " << transactionReference << endl;
    }

    bool checkStatus(long ref)
    {
        cout << "LegacyGateway: Checking status for ref: " << ref << endl;
        return paymentSuccessful;
    }

    long getReferenceNumber()
    {
        return transactionReference;
    }
};

// Adding Adapter
class LegacyGatewayAdapter : public PaymentProcessor
{
private:
    LegacyGateway *legacyGateway;
    long currentRef;

public:
    LegacyGatewayAdapter(LegacyGateway *legacyGateway) : legacyGateway(legacyGateway), currentRef(0) {}

    void processPayment(double amount, string currency) override
    {
        cout << "Adapter: Translating processPayment() for " << amount << " " << currency << endl;
        legacyGateway->executeTransaction(amount, currency);
        currentRef = legacyGateway->getReferenceNumber();
    }

    bool isPaymentSuccessful() override
    {
        return legacyGateway->checkStatus(currentRef);
    }

    string getTransactionId() override
    {
        return "LEGACY_TXN_" + to_string(currentRef);
    }
};

int main()
{
    cout << "--- Using Modern Processor ---" << endl;
    InHousePaymentProcessor processor;
    CheckoutService checkout(&processor);
    checkout.checkout(199.99, "USD");
    /*
    Everything works smoothly. You’ve decoupled your checkout business logic from the underlying payment implementation, allowing future flexibility. Great job so far.

    Now management drops a new requirement: integrate with a legacy third-party payment provider. Its SDK is battle-tested and reliable,
    but its interface looks nothing like yours.

    And here is the constraint:

    You cannot change CheckoutService, it is used system-wide and depends on PaymentProcessor
    You cannot modify LegacyGateway, it is from an external vendor
    But you must make them work together
    What you need is a translator, a class that sits between CheckoutService and LegacyGateway, adapting the incompatible interface into one that works with your system.

    This is exactly what the Adapter Design Pattern does.
    */

    // Legacy gateway through adapter
    cout << "\n--- Using Legacy Gateway via Adapter ---" << endl;
    LegacyGateway legacy;
    LegacyGatewayAdapter adapter(&legacy);
    CheckoutService legacyCheckout(&adapter);
    legacyCheckout.checkout(75.50, "USD");
    return 0;
}