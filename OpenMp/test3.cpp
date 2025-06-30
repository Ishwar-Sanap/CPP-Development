#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

int main()
{
#pragma omp parallel num_threads(4)
    {

#pragma omp critical
        {
            // unnamed critical — shared global lock
            //Only one thread can enter any unnamed critical section at a time — even if they are in different parts of code.
        }

#pragma omp critical(A)
        {
            // named critical A — uses lock A
        }

#pragma omp critical(A)
        {
            // same lock A — can't be entered by more than 1 thread
        }

#pragma omp critical(B)
        {
            // different lock — can be executed in parallel with critical(A)
        }

        return 0;
    }

    //	- critical(A) and critical(A) → use the same lock → only one thread at a time can enter either of them.
// critical(B) → uses a different lock → can run at the same time as critical(A).
}