#include <iostream>
#include <string>
using namespace std;

/*
Key Points:

Static members belong to the class, not individual objects
Must be initialized outside the class (except inline static in C++17)
Static methods can only access static members
Common uses: counters, shared configuration, singleton pattern
Access via ClassName::staticMember or object.staticMember

*/
class BankAccount
{
private:
    string accountNumber;
    double balance;

    // Static data member - shared by all instances
    static double interestRate;
    static int totalAccounts;

public:
    BankAccount(const string &accNum, double bal)
        : accountNumber(accNum), balance(bal)
    {
        totalAccounts++; // Increment for each new account
    }

    ~BankAccount()
    {
        totalAccounts--;
    }

    // Static method - can only access static members
    static void setInterestRate(double rate)
    {
        interestRate = rate;
        // balance = 100;  // ERROR: Cannot access non-static member
    }

    static double getInterestRate()
    {
        return interestRate;
    }

    static int getTotalAccounts()
    {
        return totalAccounts;
    }

    // Non-static method - can access both static and non-static
    void applyInterest()
    {
        balance += balance * interestRate;
    }

    void display() const
    {
        cout << "Account: " << accountNumber
             << ", Balance: $" << balance << endl;
    }

    double getBalance() const
    {
        return balance;
    }
};

// Static member initialization (MUST be done outside class)
double BankAccount::interestRate = 0.05; // 5% default
int BankAccount::totalAccounts = 0;

// Practical example: Singleton pattern using static
class DatabaseConnection
{
private:
    static DatabaseConnection *instance;
    string connectionString;

    // Private constructor prevents direct instantiation
    DatabaseConnection(const string &connStr)
        : connectionString(connStr)
    {
        cout << "Database connection created" << endl;
    }

    // Delete copy constructor and assignment
    DatabaseConnection(const DatabaseConnection &) = delete;
    DatabaseConnection &operator=(const DatabaseConnection &) = delete;

public:
    // Static method to get single instance
    static DatabaseConnection *getInstance(const string &connStr = "default")
    {
        if (instance == nullptr)
        {
            instance = new DatabaseConnection(connStr);
        }
        return instance;
    }

    static void destroyInstance()
    {
        delete instance;
        instance = nullptr;
        cout << "Database connection destroyed" << endl;
    }

    void query(const string &sql)
    {
        cout << "Executing: " << sql
             << " on " << connectionString << endl;
    }
};

// Initialize static pointer
DatabaseConnection *DatabaseConnection::instance = nullptr;

int main()
{
    cout << "=== Static Members Demo ===" << endl;

    // Access static method without object
    cout << "Initial interest rate: "
         << BankAccount::getInterestRate() << endl;

    BankAccount::setInterestRate(0.07); // 7%

    BankAccount acc1("ACC001", 1000);
    BankAccount acc2("ACC002", 2000);
    BankAccount acc3("ACC003", 1500);

    cout << "Total accounts: "
         << BankAccount::getTotalAccounts() << endl;

    // All accounts share the same interest rate
    acc1.applyInterest();
    acc2.applyInterest();
    acc3.applyInterest();

    acc1.display();
    acc2.display();
    acc3.display();

    cout << "\n=== Singleton Pattern Demo ===" << endl;

    // Get single instance
    DatabaseConnection *db1 = DatabaseConnection::getInstance("Server1");
    DatabaseConnection *db2 = DatabaseConnection::getInstance("Server2");

    // Both point to same instance
    cout << "db1 == db2: " << (db1 == db2) << endl;

    db1->query("SELECT * FROM users");
    db2->query("INSERT INTO logs VALUES (...)");

    DatabaseConnection::destroyInstance();

    return 0;
}