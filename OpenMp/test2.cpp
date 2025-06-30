#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

/*
	In parallel code, every thread might calculate a part of the result. reduction lets OpenMP:
		• Give each thread its own private copy of the variable (like sum, max, etc.).
		• At the end, combine all private values into a final global result safely.
		• Supported operations : (+ , -, *, &, min, max)


*/

void executeSections()
{
    /*
     What is #pragma omp sections?
    It’s used to execute distinct code blocks in parallel, where each thread handles one section
    Each section is executed once by any available thread in the team. (Note: Which thread runs which section is not fixed.)
    
     Use Case:
    Tasks are independent, not loop-based.
    For example, reading a file, processing data, and writing results — all in parallel.

    */
    #pragma omp parallel
    {
        #pragma omp sections
        {

            #pragma omp section
            {
                cout<<"section 1 executed by  Thread : " << omp_get_thread_num()<<endl; 
            }
            #pragma omp section
            {
                cout<<"section 2 executed by  Thread : " << omp_get_thread_num()<<endl; 
            }
            #pragma omp section
            {
                cout<<"section 3 executed by  Thread : " << omp_get_thread_num()<<endl; 
            }
        }
    }
}

int main()
{
    int arr[10] = {20, 5, 8, 2, 77,122, 5, 18, 82, 77};

    int maxEle = arr[0];
    int x = 10;
#pragma omp parallel for reduction(max:maxEle) 
    for (int i = 0; i < 10; i++)
    {
        if(arr[i] > maxEle)
            maxEle = arr[i];

    }

    cout << maxEle << endl;

    executeSections();

}