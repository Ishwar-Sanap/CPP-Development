
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

#include <iostream>
using namespace std;

mutex forks[5];

/*
There are 5 philosophers (P0–P4)
There are 5 forks (F0–F4)
Each philosopher needs two forks to eat:
Left fork
Right fork

A philosopher alternates between:

Thinking
    ↓
Hungry
    ↓
Eating
    ↓
Thinking

Dining Philosophers models multiple threads competing for shared resources. 
A naive implementation can deadlock when every philosopher acquires one fork and waits for the second. 
The standard solution is to enforce a global lock ordering or use std::lock() to atomically acquire both forks, thereby eliminating circular wait and preventing deadlock.
*/
void philosopher(int id)
{
    // get left and right fork
    int left = id;
    int right = (id + 1) % 5;

    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Philosopher : " << id << " thinking\n";

    /*
    // C++11/14 — verbose
    std::lock(forks[left], forks[right]);
    std::lock_guard<std::mutex> ga(forks[left], std::adopt_lock);
    std::lock_guard<std::mutex> gb(forks[right, std::adopt_lock); // std::adop_lock is used to give owenership to lock_guard<> class to unlock when goes out of scope

    // C++17 — clean
    std::scoped_lock lock(forks[left], forks[right]);   // same deadlock-avoidance, RAII, one line

    */
    // scoped_lock is wrapper class, that uses std::lock() to mangle multiple locks
    scoped_lock sc(forks[left], forks[right]);

    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Philosopher : " << id << " eating\n";
}

int main()
{
    vector<thread> philosophers;

    for (int i = 0; i < 5; i++)
    {
        thread t(philosopher, i);
        philosophers.push_back(move(t));
    }

    for (auto &ph : philosophers)
    {
        ph.join();
    }

    return 0;
}