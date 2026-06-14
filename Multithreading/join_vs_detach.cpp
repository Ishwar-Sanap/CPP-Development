#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void worker(const string &name, int delay_ms)
{
    this_thread::sleep_for(delay_ms * 1ms);
    cout << name << " finished\n";
}

void worke2(const string &name, int delay_ms)
{
    this_thread::sleep_for(delay_ms * 1ms);
    cout << name << " finished\n";
}

/*

// join()
// 0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
// 1. Double join will result into program termination.
// 2. If needed we should check thread is joinable before joining. ( using joinable() function)

// detach()
// 0. This is used to detach newly created thread from the parent thread.
// 1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and
double detach() will result into program termination.
// 2. If we have detached thread and main function is returning early then the detached thread execution is suspended.

// NOTES:
// Either join() or detach() should be called on thred object, otherwise during thread object's destructor it will
// terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.

*/

int main()
{
    cout << "Main Thread started\n";

    thread t1(worker, "t1", 200);
    t1.join(); // /main thread is waiting to finish execution by thread t1

    // t1.join(); // don't call join() or detach() method more than once , if you called it terminates the programme with core dumped issue 

    //Always check using t1.joinable() function before using join() or detach() if you are not sure.. 
    // if you have alredy called t1.join() or t1.detach() then t1.joinable() becmoes false..
    if(t1.joinable())
    {
        t1.join();
    }


    cout << "main: join example finished\n\n";

    cout << "main: starting detach example\n";

    thread t2(worke2, "t2", 3000);
    t2.detach(); // main thread is not waiting to finish execution by thread t2

    //detached thread t2 launched, but main continues immediately


    //So if your main thread ends early, the whole process can terminate, and the detached thread will not be allowed to finish safely.

    cout << "Main exiting program\n";

    return 0;
}