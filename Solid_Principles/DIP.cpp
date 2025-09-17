#include <bits/stdc++.h>
using namespace std;

// Dependency Inversion Principle (DIP)
// High-level modules should not depend on low-level modules. Both should depend on abstractions.
// Your business logic (high-level) shouldn’t directly depend on concrete classes (low-level).
// Instead, both should depend on interfaces (abstractions).

// Step 1: Define the abstraction (INotificationSender)

class INotificationSender
{
public:
    virtual void send(string message) = 0;
    virtual ~INotificationSender() {}
};

// Step 2: Low-level modules (Concrete implementations)

class EmailSender : public INotificationSender
{
public:
    void send(string message) override
    {
        cout << "[Email] Sending message: " << message << endl;
    }
};

class SMSSender : public INotificationSender
{
public:
    void send(string message) override
    {
        cout << "[SMS] Sending message: " << message << endl;
    }
};

// Step 3: High-level module that depends on abstraction

class NotifierService
{
    INotificationSender *sender; // Depends on abstraction

public:
    NotifierService(INotificationSender *s) : sender(s) {}

    void notifyUser(string message)
    {
        sender->send(message);
    }
};

int main() {
    EmailSender email;
    SMSSender sms;

    NotifierService emailService(&email);
    NotifierService smsService(&sms);

    emailService.notifyUser("Your order has been shipped.");
    smsService.notifyUser("Your OTP is 123456.");

    return 0;
}