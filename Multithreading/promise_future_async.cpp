#include <bits/stdc++.h>
using namespace std;

/*
What is std::promise?
std::promise is an object used by one thread to send a value (or exception) to another thread.

Think of it like:
📤 taks side: Setting the result

A promise holds a value that will be available in the future.
You call promise.set_value() from the producer thread.
Or in case of failure, promise.set_exception().

What is std::future?
std::future is the receiver of the value produced by promise.

User side: Getting the result

You call future.get() to retrieve the result.
future.get() blocks until the promise sets the value.



When to use Promise/Future?
Use promise + future when:

You want one thread to send a result to another.

Need to explicitly control the producer.

Return values from threads without global variables.

Handle exceptions safely.
*/

/*
future does not track the promise object itself. It tracks the same shared state that the promise writes into.

In your code, this happens:

promise<int> p1;
future<int> f1 = p1.get_future();
This creates a shared state and gives f1 a handle to it.
thread t1(getSqure, 10, move(p1));
p1 is moved into the thread, not copied.
Inside getSqure(int num, promise<int> pr), pr is a local parameter, but it still owns that same shared state.
pr.set_value(res); writes the result into the shared state.
f1.get() reads from that same shared state.
So even though pr is passed by value, the value being "shared" is not the promise object itself. The promise is just a handle to a shared state, and moving it still preserves that connection.

A useful mental model:

promise = writer handle
future = reader handle
shared state = the actual storage both refer to
One extra detail: std::promise is move-only, so this pattern only works because you pass it with move(p1)

*/
void getSqure(int num, promise<int> pr)
{
    int res = num * num;
    pr.set_value(res);
}

int getSqureAsyn(int num)
{
    int res = num * num;
    return res;
}
int main()
{
    promise<int> p1;
    future<int> f1 = p1.get_future();

    promise<int> p2;
    future<int> f2 = p2.get_future();

    thread t1(getSqure, 10, move(p1));

    thread t2(getSqure, 8, move(p2));

    cout << "Waiting for value...\n";

    int result1 = f1.get(); // blocks main thread until get the result from
    int result2 = f2.get(); // blocks main thread until get the result from

    cout << "Received: " << result1 << "\n";
    cout << "Received: " << result2 << "\n";

    t1.join();
    t2.join();

    /*async Internally, it uses promise + shared state + thread , and retrun result as future*/
    f1 = async(launch::async, getSqureAsyn, 10);

    /*
    C++ allows two possibilities:

    1️⃣ std::launch::async → runs in a new thread (non-blocking)
    2️⃣ std::launch::deferred → runs only when you call .get() (blocking)
    */

    cout << "Squre of 10 : " << f1.get() << endl; // get() is always blocking call until resuts are not ready..

    return 0;
}