#include <bits/stdc++.h>
using namespace std;

template <typename T>
class ThreadSafeQueue
{
private:
    queue<T> m_queue;
    mutex m_mtx;
    condition_variable m_cv;

public:
    void push(T value)
    {
        {
            lock_guard<mutex> lg(m_mtx);
            m_queue.push(value);
        }

        // After adding data into queue notify the waiting threds
        m_cv.notify_all();
    }

    // Blocking pop  (if queue is empty then wait util data is arrived) i.e thread goes in sleep
    void pop()
    {
        unique_lock<mutex> ul(m_mtx);

        // If predicate/lambda condition is false, then thread will wait
        // else continue further execution
        m_cv.wait(ul, [this]
                  { return !m_queue.empty(); });

        m_queue.pop();
    }

    // Non blocking pop
    bool try_pop()
    {
        lock_guard<mutex> lg(m_mtx);

        if (m_queue.empty())
            return false;

        m_queue.pop();

        return true;
    }
    T front()
    {
        lock_guard<mutex> lg(m_mtx);
        if (m_queue.empty())
            return {};

        return m_queue.front();
    }

    bool empty()
    {
        lock_guard<mutex> lg(m_mtx);
        return m_queue.empty();
    }
};

void producer(ThreadSafeQueue<int> &tq, int id)
{
    for (int i = 1; i <= 10; i++)
    {
        cout << "Producer thread : " << id << " pushing " << i << endl;
        tq.push(i);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer(ThreadSafeQueue<int> &tq, int id)
{
    while (true)
    {
        int val = tq.front();
        tq.pop();
        cout << "Consumer thread : " << id << " consuming " << val << endl;

        // set for safely exit the thread loop..
        if (val == -1)
            break;

        this_thread::sleep_for(chrono::milliseconds(800));
    }
}
int main()
{
    ThreadSafeQueue<int> tq;

    thread t1(producer, ref(tq), 1);
    thread t2(producer, ref(tq), 2);
    thread t3(consumer, ref(tq), 3);
    thread t4(consumer, ref(tq), 4);

    tq.push(-1);
    tq.push(-1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}