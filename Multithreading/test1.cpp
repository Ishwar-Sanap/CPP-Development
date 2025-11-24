#include <iostream>
#include <thread>
using namespace std;
// thread library only support C++ 11 and later verisons

void func1(int x, string str)
{
    cout << "Func1 is executing by thread t1" << endl;
    // Might be this fucntion performs some heavy task and needs more time to complete

    thread tf1([]{
        cout<<"Inside lambda of thread tf1"<<endl;
    });

    //As func1 is called by thread t1, once it called func1 is creating another thread and now t1, and tf1 will also work parallely
    // so t1 has to wait or detach from tf1 to avoid run time core dump error..

    tf1.join();
    // tf1.detach();

    cout<<"end of func1 "<<endl;
}

//Return value of this func2, will not be used since, this function is starting fun of therad and it called by OS
int func2(int &x, int y)
{
    x = x + y;

    cout<<"Value of x in t3 thread : " << x <<endl;
    return -1;
}

int main()
{
    cout << "Main thread is started.." << endl;

    // Threads will excute the task parallely
    //But we can't decide, In which sequence threads will be excuted, it totally depends on OS how it shedule the threads.

    //When you create any thread, you have to pass starting function for it, so thread will start it's executing. ex : func1
    thread t1(func1, 10, "Hello");

    //Lambda function as a starting function for thread t2
    thread t2([](string str){ 
        cout << "Inside thread t2 Lambda function : " << str << endl; 
        
        // for(int i = 1; i<= 1111111; i++){}
        
        cout << "Thread t2 Lambda function completed : " << endl; 
    }, "Hello");

    // join is used for waiting the main thred execution until t1, t2 threads completes it's execution
    // if we don't use jon then main thred will continue it's execution early and then process will be terminated,
    // but if t1 or t2 is still excuting then that will be aborted and will get runtime core dump issue.

    t1.join();
    t2.join();

    // t2.detach();  // t2.detach()  It will detached main thread from it, 
    //so main thread don't wait for completing execution of thread2 but there is no runtime issue


    //By default value will be pass to starting function as Call by value. 
    // we can also passed it by ref using 

    int x = 10, y = 20;
    thread t3(func2, ref(x), y);
    t3.join();
    cout<<"Value of x in main thread : " << x <<endl;  // getting update value 30, because main thred waiting until t3 completes execution

   

    cout << "Main thread completed execution.." << endl;
    return 0;
} 