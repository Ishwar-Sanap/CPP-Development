#include <iostream>
using namespace std;

void fun(int b)
{
    if (b == 0)
        return;

    cout << b << endl;
    fun(b--);
}

// Calling foo() recursively will cause Stack Overflow:
// Typical Linux process stack size is around 8 MB (check with ulimit -s).

// A stack frame contains memory for below :
// Function parameters
// Local variables
// Return address
// Saved registers

void foo()
{
    int arr[1000000]; // ~4 MB
    cout << "called" << endl;
    foo();
}
// 1st call → 4 MB used
// 2nd call → 8 MB used
// 3rd call → exceeds 8 MB → stack overflow

/*
arr is allocated on the heap, so it does not significantly increase stack usage.
Each recursive call still creates a new stack frame, so recursion can still cause a stack overflow.
Since the allocated memory is never freed, the program also leaks memory and may fail with heap exhaustion (std::bad_alloc) before stack overflow occurs.
*/
void funDynamic()
{
    int *arr = new int[1000000]; // ~4 MB
    cout << "called" << endl;
    funDynamic();
}

/*Is the stack size per process or per thread?

On Linux with POSIX threads:

Each thread gets its own stack.
Main thread often has an 8 MB default stack.
New threads created with pthread_create() also commonly get an 8 MB default stack (implementation dependent).

So if you have:

std::thread t1(...);
std::thread t2(...);

you typically have:

Thread 1 Stack : 8 MB
Thread 2 Stack : 8 MB
Main Thread    : 8 MB

Each stack is independent.

How to check the stack size?

Linux shell:

ulimit -s

Output:

8192

This means 8192 KB = 8 MB stack size limit for the thread stack.

*/

void largeStackSpace()
{
    // int size --> 4Bytes
    //   1KB --> 1024 Bytes
    //   1MB --> 1024 KB

    // 1kB --> 1024/4 = 256 Integers can be stored in 1KB

    // 1MB -> 1024 * 256 = 2,62,144 Integers can be stored

    // Typical Linux process stack size is around 8 MB (check with ulimit -s).

    int arr[3000000]; // ~12 MB
    // Since 12 MB > 8 MB, entering largeStackSpace() will likely cause a stack overflow and the program may crash with a segmentation fault.
}
int main()
{
    // fun(10);
    // foo();

    // largeStackSpace();

    // funDynamic();

    /*
    Stack Overflow:
    A specific problem: the program uses more stack memory than allowed.
    Usually happens due to deep recursion or huge local variables.	Happens when accessing invalid memory.
    Often results in a segmentation fault on Linux.

    Segmentation Fault:
    A general memory access violation.
    Symptom/error reported by OS
    Can be caused by many things, including stack overflow, accessing freed memory, Dereferencing a null pointer
    */
    int *ptr = new int(10);
    cout << *ptr << endl;

    delete ptr;
    ptr = nullptr;
    cout << *ptr << endl; // Segmentation fault (core dumped)

    return 0;
}