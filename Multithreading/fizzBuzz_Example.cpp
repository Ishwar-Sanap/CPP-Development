#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
using namespace std;

// function<void()> is basically “a variable that stores a function with no arguments and no return value.”
/*
Why use it?
std::function lets you pass:

regular functions
lambda expressions
function objects (functors)
*/

// https://leetcode.com/problems/fizz-buzz-multithreaded/description/

class FizzBuzz
{
private:
    int n;
    mutex mt;
    condition_variable cv;
    int i;

public:
    FizzBuzz(int n)
    {
        this->n = n;
        i = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {

        while (true)
        {
            unique_lock<mutex> ul(mt);
            cv.wait(ul, [this]()
                    { return ((i % 3 == 0 && i % 5 != 0) || i > n); });

            if (i > n)
                break;
            printFizz();
            i++;

            ul.unlock();
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
        while (true)
        {
            unique_lock<mutex> ul(mt);
            cv.wait(ul, [this]()
                    { return i % 5 == 0 && i % 3 != 0 || i > n; });

            if (i > n)
                break;
            printBuzz();
            i++;

            ul.unlock();
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
        while (true)
        {
            unique_lock<mutex> ul(mt);
            cv.wait(ul, [this]()
                    { return i % 5 == 0 && i % 3 == 0 || i > n; });

            if (i > n)
                break;

            printFizzBuzz();
            i++;

            ul.unlock();
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {

        while (true)
        {
            unique_lock<mutex> ul(mt);
            cv.wait(ul, [this]()
                    { return (i % 3 != 0 && i % 5 != 0) || i > n; });

            if (i > n)
                break;
            printNumber(i);

            i++;

            ul.unlock();
            cv.notify_all();
        }
    }
};

void printNum(int x)
{
    cout << x << endl;
}

void printFizz()
{
    cout << "Fizz" << endl;
}
void printBuzz()
{
    cout << "Buzz" << endl;
}
void printFizzBuzz()
{
    cout << "FizzBuzz" << endl;
}
int main()
{

    FizzBuzz obj(15);

    thread t1(&FizzBuzz::buzz, &obj, printBuzz);
    thread t2(&FizzBuzz::fizz, &obj, printFizz);
    thread t3(&FizzBuzz::fizzbuzz, &obj, printFizzBuzz);
    thread t4(&FizzBuzz::number, &obj, printNum);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}