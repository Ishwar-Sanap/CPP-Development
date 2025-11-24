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
mutex mt;

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
        count++;                   // critical section...

        // Guarantees automatic unlock when ul goes out of scope (RAII).
    }
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

    thread t1(fun2, 1);
    thread t2(fun2, 2);

    t1.join();
    t2.join();

    cout << "Count : " << count << endl;

    cout << "End main thread : " << endl;
    return 0;
}