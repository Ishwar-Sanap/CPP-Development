#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
int balance = 0;

/*
A condition variable is a synchronization primitive used to make one or more threads wait until a particular condition becomes true.

Without condition variables, a thread may continuously check a condition in a loop (busy waiting), wasting CPU cycles.

*/
void depositeMoney(int money)
{
    {
        lock_guard<mutex> lg(mtx);
        balance += money;
        cout << "Amount Added, Current balance : " << balance << " \n";
    }

    // After unlock resource then notify ohter threads
    cv.notify_one();

    //cv.notify_one();   // wakes exactly ONE waiting thread (unpredictable which one)
    //cv.notify_all();   // wakes ALL waiting threads — each re-checks predicate
                   // only one will proceed if there's only one item of work
}

void withdrawMoney(int money)
{
    unique_lock<mutex> ul(mtx);

    // wait till condition is false i.e thread is going into sleep state
    //other thread will notifies to cv object, and t2 thread get wake up and check the condition again, if condition becomes true, then thred continues further execution, else again sleep.
    //Note : When thread is sleeping cv ensure that it release the lock, and after wake up again acquire the call automatically
    cv.wait(ul, []()
            { return balance != 0; });

    if (balance < money)
    {
        cout << "Failed : Insufficient balance\n";
    }
    else
    {
        balance -= money;
        cout << "Success : money withdraw " << money << " \n";
    }

    cout << "Current balance : " << balance << " \n";
}

int main()
{

    // Assuming t1 thread started first, but to withdraw money there should be balance available,
    // and as deposite money is not yet compltes, theread t1 has to wait until the condition is not true.
    // once codition becomes true then t1 can start it's execution

    thread t1(withdrawMoney, 500);
    thread t2(depositeMoney, 1000);

    t1.join();
    t2.join();

    return 0;
}