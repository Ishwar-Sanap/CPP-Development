#include <bits/stdc++.h>
using namespace std;

/*
The Reader–Writer Problem refers to synchronizing access to shared data such that:

Multiple readers can read simultaneously
A writer must have exclusive access
No reader should read while a writer is writing
No writer should write while any reader is reading

This is used in:

Databases
Filesystems
Caches
In-memory key–value stores
Any shared read-mostly data structure

Reader–Writer Problem ensures that:
Readers read in parallel
Writers require exclusive access
Synchronization prevents race conditions, starvation & deadlocks
*/

// This can be done using  std::shared_mutex
/*
std::shared_mutex

Multiple readers can hold shared_lock
Writers take unique_lock
*/

int shared_data = 0;
shared_mutex smtx;

void writer(int id)
{
    for (int i = 0; i < 5; i++)
    {
        unique_lock<shared_mutex> ul(smtx); // exclusive lock
        shared_data++;
        cout << "Writer " << id << " Writes : " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void reader(int id)
{
    for (int i = 0; i < 5; i++)
    {
        shared_lock<shared_mutex> sl(smtx); // shared lock
        cout << "Reader " << id << " Reads : " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

/*
If you remove sleep_for, the program becomes extremely fast.
Threads will run so quickly that:

Many print statements interleave
Readers and writers don't show visible differences
Console output becomes cluttered



What does shared_mutex guarantee?
✔ No one writes while reader is reading
❌ It does NOT guarantee the reader sees the most recent write

Why?
Because:

After writer writes and releases exclusive lock
Another writer may increment again
Before reader acquires shared lock
Readers see a consistent value, but not necessarily the newest.
*/
int main()
{

    vector<thread> threads;

    // creat writer threads
    for (int i = 1; i <= 2; i++)
    {
        threads.emplace_back(writer, i);
    }

    // creat reader threads
    for (int i = 1; i <= 3; i++)
    {
        threads.emplace_back(reader, i);
    }

    for (auto &thred : threads)
        thred.join();

    return 0;
}