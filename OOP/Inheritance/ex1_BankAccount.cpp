#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

/*
Design Bank Account Hierarchy Class

Problem: Build a bank account system using inheritance. The base BankAccount class has common fields and methods for deposits and withdrawals. Specialized account types have different withdrawal rules.

Requirements:

Base BankAccount class with ownerName, accountNumber, and balance (protected). A deposit(amount) method that adds to the balance if the amount is positive. A withdraw(amount) method that subtracts from the balance if funds are sufficient and returns true/false. A displayAccount() method that prints the owner's name, account number, and formatted balance.
SavingsAccount: adds an interestRate field. Overrides withdraw() to enforce a minimum balance of $100 (the withdrawal fails if it would drop the balance below $100). Adds an applyInterest() method that increases the balance by balance * interestRate / 100.
CheckingAccount: adds an overdraftLimit field. Overrides withdraw() to allow withdrawals up to balance + overdraftLimit.
displayAccount() should work correctly for all account types without any changes to the base class.

*/
class BankAccount
{
protected:
    string ownerName;
    string accountNumber;
    double balance;

public:
    BankAccount(const string &ownerName, const string &accountNumber,
                double balance) : ownerName(ownerName), accountNumber(accountNumber), balance(balance)
    {
    }

    virtual ~BankAccount() {}

    bool deposit(double amount)
    {

        if (amount > 0)
        {
            balance += amount;
            return true;
        }

        return false;
    }

    virtual bool withdraw(double amount)
    {

        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            return true;
        }

        return false;
    }

    void displayAccount()
    {

        char buf[32];
        sprintf(buf, "$%.2f", balance);
        cout << ownerName << " (" << accountNumber << ") | Balance: " << buf << endl;
    }
};

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(const string &ownerName, const string &accountNumber,
                   double balance, double interestRate)
        : BankAccount(ownerName, accountNumber, balance), interestRate(interestRate)
    {
    }

    bool withdraw(double amount) override
    {
        if (amount > 0 && amount <= balance - 100)
        {
            balance -= amount;
            return true;
        }

        return false;
    }

    void applyInterest()
    {
        // TODO: add (balance * interestRate / 100) to balance
        balance += (balance * interestRate) / 100;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(const string &ownerName, const string &accountNumber,
                    double balance, double overdraftLimit)
        : BankAccount(ownerName, accountNumber, balance), overdraftLimit(overdraftLimit)
    {
    }

    bool withdraw(double amount) override
    {

        if (amount > 0 && amount <= balance + overdraftLimit)
        {
            balance -= amount;
            return true;
        }
        return false;
    }
};

int main()
{
    SavingsAccount savings("Alice", "SAV-001", 1000, 2.0);
    savings.displayAccount();
    cout << "Withdraw $950: " << (savings.withdraw(950) ? "true" : "false") << endl;
    savings.applyInterest();
    savings.displayAccount();

    cout << endl;

    CheckingAccount checking("Bob", "CHK-002", 500, 300);
    checking.displayAccount();
    cout << "Withdraw $700: " << (checking.withdraw(700) ? "true" : "false") << endl;
    checking.displayAccount();

    return 0;
}