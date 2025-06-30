#include <bits/stdc++.h>
#include <omp.h>

using namespace std;



/*
Syntax of OpenMP

OpenMP uses compiler directives to indicate the parallel sections of the code. 
The directives are preceded by the "#pragma" keyword and take the form:

#pragma omp <directive> [clause[,clause]...]
OpenMP directives:

"parallel": create a team of threads that execute the enclosed code block in parallel.
"for": splits a loop into smaller iterations that can be executed in parallel by different threads.
"sections": split the enclosed code block into different sections that can be executed in parallel.
"single": specifies that a code block should be executed by only one thread.
"critical": specifies that a code block should be executed by only one thread at a time.
"atomic": specifies that a variable should be accessed atomically.

ex: #pragma omp parallel
{
    // code block executes parallel.
}
    
OpenMP clause : 

#pragma omp parallel for reduction(+:sum)
openMP clause that helps safely combine (reduce) values computed by multiple threads into a single result, 
 without race conditions. supported operators( +, -, *, min, max, &)

#pragma omp parallel private(i)
Each thread gets its own uninitialized copy of the variable.

int x = 5;
#pragma omp parallel firstprivate(x)
Each thread gets its own copy of the variable, but it is initialized with the master thread’s value.
Every thread starts with x = 5, but can modify independently.

#pragma omp parallel shared(sum)
All threads share the same instance of the variable.
Must protect with atomic, critical, or reduction to avoid race conditions.



*/

//Overheads of using multiple threds??

long long getSumOfNaturalNums(int n)
{
    // parallel loops

    double start = omp_get_wtime();

    long long totalSum = 0;
    // split the for loops amoung the threds
    #pragma omp parallel for reduction(+:totalSum)
            for(int i = 1; i <= n; i++)
            {
                totalSum += i;
            }
    

    double end = omp_get_wtime();

    cout.precision(5);
    cout<<"Time elapsed : " << (end - start)<<endl;

    return totalSum;
}

int main()
{

// Content Inside the parallel region will be exeucted by multiple threads simaltaneously
// There might be chance of race conditions, when multiple threads trying to print the line on console
//so then you will see : something unexpected behaviour Thread : Thread : Thread : 041

// TO avoid race conditions we have to use critical region : --> 
//where only one thread at a time execute the code and other maintain the queue..

// shared and private memory between threads..

int x = 11; // this varible is shared between all threads so any of the thread can update/modify the x
#pragma omp parallel
    {
        int y = 21; // this is private, each thread will have it's own copy of y
#pragma omp critical
        {

            cout << "Thread : " << omp_get_thread_num() << endl;
            x++;
            cout<<x << endl;

            y++;
            cout<<y<<endl;
        }
    }

    long long sum = getSumOfNaturalNums(1000);
    cout<<"Sum is : "<<sum<<endl;
    return 0;
}