#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <chrono>

using namespace std;

typedef long long ll;

ll getSingleThreadedSum(vector<int> &arr)
{
    ll rest = accumulate(arr.begin(), arr.end(), 0LL);
    return rest;
}

void getPartialSum(vector<int> &arr, int start, int end, ll &currSum)
{
    currSum = accumulate(arr.begin() + start, arr.begin() + end, 0LL);
}

ll getMultiThreadedSum(vector<int> &arr)
{
    int n = arr.size();

    // Returns a value that hints at the number of hardware thread contexts.
    int num_threads = thread::hardware_concurrency(); // number of logical CPU cores
    num_threads = min(num_threads, n);

    // We split array into multiple parts, and each part sum will be done by seperate thread parallely.
    int chunk_size = n / num_threads;

    vector<ll> partial_sum(num_threads, 0LL);
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? n : start + chunk_size;

        ll currSum = 0;

        // thread t(getPartialSum, ref(arr), start, end, ref(partial_sum[i]));
        // threads.push_back(t);  // ERROR
        // std::thread represents a running system thread
        // You cannot duplicate a running thread (makes no sense), so C++ don't allow to copy thread into vector using push_back(t)

        // C++ allows move semantics only or direct creating thread in vector

        // Constructs the thread object directly in the vector's memory
        threads.emplace_back(getPartialSum, ref(arr), start, end, ref(partial_sum[i]));
    }

    for (auto &thread : threads)
    {
        thread.join(); // waiting until all threads completes execution
    }

    ll result = accumulate(partial_sum.begin(), partial_sum.end(), 0LL);
    return result;
}

int main()
{
    int MAX_SIZE = 10000000;

    vector<int> arr(MAX_SIZE, 1);

    ll total_sum = 0;

    auto startTime = chrono::high_resolution_clock::now();
    total_sum = getSingleThreadedSum(arr);
    auto endTime = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, std::milli>(endTime - startTime).count();

    cout << "Sum single thread : " << total_sum << " time take --> " << ms << " ms" << endl;

    startTime = chrono::high_resolution_clock::now();
    total_sum = getMultiThreadedSum(arr);
    endTime = chrono::high_resolution_clock::now();
    ms = chrono::duration<double, std::milli>(endTime - startTime).count();

    cout << "Sum multi threadead : " << total_sum << " time take --> " << ms << " ms" << endl;

    /*
    NOTE :
    Multithreading helps only when work per thread is large
    AND you have enough CPU cores
    AND threads do not fight each other.

    for smallers taks Multithreading Makes Performance Worse due to :
    Thread creation overhead
    Context switching overhead
    Memory synchronization overhead

    So for small tasks, these overheads are bigger than the work itself, making it slower. so use single threaded logic...
    */
    return 0;
}