#include <bits/stdc++.h>
using namespace std;

int main()
{

    /*

   std::remove(begin, end, value)

   Removes all elements equal to value from the given range.
   Actually moves non-removed elements forward.

   Returns an iterator to the new logical end.

   std::remove_if(begin, end, predicate)

   Removes all elements that satisfy a predicate (a condition function). lambda function

   ❗ Important:
   It does NOT change container size.

   Returns new logical end.
   */
    vector<int> arr = {1, 2, 4, 6, 5, 6, 8};

    auto it = remove(arr.begin(), arr.end(), 6);
    // arr.resize(distance(arr.begin(), it)); // modifying the vector
    // or
    arr.erase(it, arr.end()); /// actually removing the elements.

    for (int ele : arr)
        cout << ele << " ";

    cout << endl;

    vector<int> arr2 = {1, 2, 4, 6, 5, 6, 8};

    // moving event elemnet at the end of vecotr to remove
    auto it2 = remove_if(arr2.begin(), arr2.end(), [](int ele)
                         { return ele % 2 == 0; });

    arr2.erase(it2, arr2.end());

    for (int ele : arr2)
        cout << ele << " "; // 1 5

    cout << endl;

    vector<int> transFormedOutput;
    transFormedOutput.assign(arr2.size(), 0);

    // squre of each element from arr2
    transform(arr2.begin(), arr2.end(), transFormedOutput.begin(), [](int x)
              { return x * x; });

    for (int ele : transFormedOutput)
        cout << ele << " "; // 1 25

    cout << endl;

    return 0;
}