#include <iostream>
#include "ctpl_stl.h"  //using third party library
using namespace std;


// We can also implement our own thread pool class 

/*
What are Thread Pools?

They are a group of threads that are initially created, while waiting for a job or task to execute.

IT is software design pattern that manages a collection of pre-created, reusable worker threads to efficiently 
execute multiple tasks concurrently. Instead of creating and destroying a new thread for every single task, 
the thread pool reuses existing threads, significantly reducing performance overhead and latency. 

*/

int main()
{
    int MAX_THREADS = 8;
    ctpl::thread_pool tp(MAX_THREADS);  //pre creating number of threads

    for (int i = 0; i < 20; i++)
    {
        tp.push([](int id) {
            cout<<"Running thread ID : " << id <<endl;
        });
    }
}