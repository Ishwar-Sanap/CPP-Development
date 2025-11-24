#include <bits/stdc++.h>
using namespace std;

/*
Deadlock in multithreading is a situation where two or more threads are permanently blocked,
each waiting for a resource (lock/mutex) that the other thread holds. As a result, none of them can continue, and the program gets stuck.
*/

mutex mt1, mt2;
mutex mt3;
recursive_mutex rmt;

void task1()
{
    lock_guard<mutex> lg(mt1);
    this_thread::sleep_for(chrono::milliseconds(100));
    lock_guard<mutex> lg2(mt2);
    cout << "Thread t1 with ID : " << this_thread::get_id() << " finished " << endl;
}

void task2()
{
    lock_guard<mutex> lg(mt2);
    this_thread::sleep_for(chrono::milliseconds(100));
    lock_guard<mutex> lg2(mt1);

    cout << "Thread t2 with ID : " << this_thread::get_id() << " finished " << endl;
}

void task3(int n)
{
    if (n < 0)
        return;

    cout << "Fun " << n << endl;

    //  deadlock: self-deadlock using simpe mutext
    // mt3.lock();

    rmt.lock();  // to avoid it using recursive mutex..

    task3(n - 1);

    // mt3.unlock();
    
    rmt.unlock();
}

// Heres the situation:

// Thread t1 is waiting for mt2, which is held by t2
// Thread t2 is waiting for mt1, which is held by t1

// ❗ Both threads are waiting on each other
// ❗ No one releases their first lock
// ❗ Program stops forever → DEADLOCK

/********************** HOW TO AVOID DEAD LOCKS  ********************** */
/*
1) Always lock mutexes in same order
 For example: always lock mt1 first, then mt2.

2) Lock both mutexes at once
     std::lock(mt1, mt2);

3) std::scoped_lock lock(m1, m2); // locks both safely

4) For recursive function use recursive_mutex


*/

int main()
{

    // thread t1(task1);
    // thread t2(task2);
    thread t3(task3, 5);

    // t1.join();
    // t2.join();
    t3.join();

    return 0;
}