#include <bits/stdc++.h>
using namespace std;

/*
Producer–Consumer Problem
What is it?

Producer–Consumer is a classic multithreading problem where:
Producer thread generates data and puts it into a shared buffer.
Consumer thread removes data from the same buffer.

Both must be synchronized so:
Producer does not write when buffer is full.
Consumer does not read when buffer is empty.
*/

queue<int> queueBuffer;
int MAX_BUFFER_SIZE = 10;

mutex mtx;
condition_variable cv;

void producer(int id)
{
    int value = 0;
    while (true)
    {   
        this_thread::sleep_for(chrono::milliseconds(500));
        unique_lock<mutex> ul(mtx);
        cv.wait(ul, [](){
           return queueBuffer.size() < MAX_BUFFER_SIZE;
        });

        /*
        callable function lambda
         lambda should return true or false:
         If returns:
        true → buffer has space → thread skip the waiting or wake up, and continue furhter execution
        false → buffer is full → keep sleeping or thread goes in waiting state and cv.wait() unlock the mutex automatically for other threads


        */

        queueBuffer.push(value);
        cout << "Producer " << id << " produces " << value << " | Buffer size: " << queueBuffer.size() << endl;
        value++;

        /*
        Because a thread waiting on a condition_variable will never wake up on its own.
        It needs another thread to signal it.
        */
        cv.notify_all();  // notify consumers threds, to check your condition again!!
    }
}

void consumer(int id)
{
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(700));
        unique_lock<mutex> ul(mtx);

        cv.wait(ul, [](){
           return !queueBuffer.empty();
        });

        /*
        lambda return 
        true → buffer has elements → thread skip the waiting or wake up, and continue furhter execution
        false → buffer is empty → keep sleeping or go in wait state  and cv.wait() unlock the mutex automatically for other threads
        */

        int value = queueBuffer.front();
        queueBuffer.pop();
        cout << "Consumer " << id << " consumed " << value << " | Buffer size: " << queueBuffer.size() << endl;

        cv.notify_all(); // notify produceres threds i.e  notify says:  Hey waiting threads, check your condition again!
    }
}

int main()
{
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join();
    p2.join();
    c1.join();
    c2.join();


    return 0;
}