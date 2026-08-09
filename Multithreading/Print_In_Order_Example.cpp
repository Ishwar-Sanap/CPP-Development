
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
using namespace std;

// https://leetcode.com/problems/print-in-order

class Foo
{
    int turn;
    mutex mt;
    condition_variable cv;

public:
    Foo() : turn(0)
    {
    }

    void first(function<void()> printFirst)
    {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        turn = 2;
        cv.notify_all();
    }

    void second(function<void()> printSecond)
    {
        unique_lock<mutex> ul(mt);
        cv.wait(ul, [this]()
                { return turn == 2; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        turn = 3;
        cv.notify_all();
    }

    void third(function<void()> printThird)
    {
        unique_lock<mutex> ul(mt);
        cv.wait(ul, [this]()
                { return turn == 3; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        turn = 1;
        cv.notify_all();
    }
};

void printFirst()
{
    cout << "First" << endl;
}
void printSecond()
{
    cout << "Second" << endl;
}
void printThird()
{
    cout << "Third" << endl;
}
int main()
{

    Foo obj;

    thread t3(&Foo::third, &obj, printThird);
    thread t2(&Foo::second, &obj, printSecond);
    thread t1(&Foo::first, &obj, printFirst);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}