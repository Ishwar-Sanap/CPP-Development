#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename container>
typename container::value_type sum(container arr) // what element it store in stl container can be deduce using vlaue_type
{
    typename container::value_type res = typename container::value_type{}; // calling default constructor for assigning default values.
    for (auto ele : arr)
    {
        res += ele;
    }

    return res;
}

// We can also use auto for return type insted of typename container::value_type

void printArr(vector<int>&arr){
    for(int ele : arr){
        cout<<ele<<" ";
    }
    cout<<endl;
}
int main()
{
    // vector<int> arrInt = {1, 2, 3, 4, 5};
    // vector<double> arrdble = {1.5, 2.5, 3.5, 4.5, 5.5};
    // list<int> l1 = {2, 4, 6, 8};
    // auto res1 = sum(arrInt);
    // auto res2 = sum(arrdble);
    // auto res3 = sum(l1);
    // cout << "Array sum : " << res3 << endl;

    vector<int> arr = {1, 2, 5};

    cout << "cap : " << arr.capacity() << endl;
    cout << "size : " << arr.size() << endl;
    printArr(arr);
    
    arr.resize(8);
    arr.clear();
    printArr(arr);

    cout << "cap : " << arr.capacity() << endl;
    cout << "size : " << arr.size() << endl;

    return 0;
}