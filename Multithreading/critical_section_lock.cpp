#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

/*
 Mutex : It stands for Mutual Exclusion Object.
 meaning it is a lock used to ensure that only one thread or process can access a shared resource or critical section of code at a time.
 A mutex enforces strict ownership. Only the thread that locks the mutex can unlock it.
*/

// Critcal section :
/*
a critical section is a block of code that must not be executed by more than one thread at the same time.
It protects shared data or resources from being accessed concurrently, which would otherwise lead to race conditions or corrupted data.

A critical section ensures mutual exclusion, meaning only one thread can enter that protected region at a time.
*/

// Fun1 is peforming sum task and that function is parallely executed by multiple threads..

int count = 0;
mutex mt; // It is a binary flag with a guarantee: only one thread can "own" it at a time

void fun1(int id)
{
    for (int i = 0; i < 50000; i++)
    {
        mt.lock();
        count++; // critical section...
        mt.unlock();
    }
    /*
        If any exception happens inside the critical section (even in the future), the function will exit without calling mt.unlock(), causing a deadlock.
        This is why manual lock()/unlock() is considered unsafe in modern C++.
    */
}

void fun2(int id)
{
    for (int i = 0; i < 50000; i++)
    {
        {
            lock_guard<mutex> lg(mt); // A RAII-style automatic lock Unlock for a mutex.
            count++;                  // critical section...
        }

        // once the scope of lg object finished it automatically unlock the mutex
    }
}

void fun3(int id)
{
    for (int i = 0; i < 50000; i++)
    {
        unique_lock<mutex> ul(mt); // A RAII-style automatic lock Unlock for a mutex.  +  manual Cotrol
        count++;
        // critical section...
        // Manual control also
        // ul.lock();
        //  ul.unlock();

        // Guarantees automatic unlock when ul goes out of scope (RAII).
    }
}

int bufferCnt = 0;
/*

fun4 is recursive, but it does not lock the same mutex again in the same thread. It just calls itself recursively, and each recursive call does not acquire the mutex again unless you add locking inside the function. So a normal std::mutex is sufficient.

Simple rule
Use std::mutex for normal mutual exclusion.

Use std::recursive_mutex only if recursion/re-entry on the same thread is required.
So the answer is: No, a recursive mutex is not needed here unless you intentionally lock the same mutex again from the same thread.
*/

mutex mtx;
void fun4(const string &t, int i)
{
    if (i <= 0)
        return;

    fun4(t, --i);

    {
        lock_guard<mutex> lk(mtx);
        bufferCnt++;
        cout << "Thread " << t << " : " << bufferCnt << endl;
    }
}

recursive_mutex rmtx;
// But still for understanding purpose using recursive mutex
/*
Why it works:

rmtx.lock() is acquired before the recursive call.
The same thread calls fun5() again, so it tries to lock the same mutex a second time.
std::recursive_mutex allows that, because the same thread can own the lock multiple times.
Then rmtx.unlock() releases one level at a time on the way back.
So this code will compile and run, and it protects the shared section.

But one important note:

This is not the best style in real code.
You should usually use lock_guard / unique_lock instead of manual lock() / unlock().
Also, locking the whole recursive path is heavier than necessary.
*/

void fun5(const string &t, int i)
{
    if (i <= 0)
        return;

    rmtx.lock();
    fun5(t, --i);
    bufferCnt++;
    cout << "Thread " << t << " : " << bufferCnt << endl;
    rmtx.unlock();
}

/*
Real-world rule of thumb
If the work inside the loop is small, lock outside.
If each iteration does heavy or independent work, lock inside so threads don’t block each other.


When Should You Use Which?
Use lock_guard when:
    • You just need simple locking
    • Lock/unlock only once in a scope
    • You want faster and cleaner code

Use unique_lock when:
    • You want to cotrol unlock manually also
    • You want to relock later
    • You need try_lock()
    • You need defer_lock
    • You use condition_variable
    • You need movable lock objects
You lock multiple mutexes safely with std::lock()
*/
int main()
{
    cout << "Start main thread : " << endl;

    // thread t1(fun2, 1);
    // thread t2(fun2, 2);

    // t1.join();
    // t2.join();

    // cout << "Count : " << count << endl;

    thread t3(fun5, "T3", 10);
    t3.join();

    thread t4(fun5, "T4", 10);
    t4.join();

    cout << "End main thread : " << endl;
    return 0;
}