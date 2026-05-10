#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    cout << "=== Vector Iterator Tests ===\n\n";

    // 1. Basic iterator usage with push_back
    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    // 2. Forward iteration using range-based for loop
    cout << "1. Range-based for loop (begin/end):\n";
    for (auto val : v1)
    {
        cout << val << " ";
    }
    cout << "\n\n";

    // 3. Forward iteration using explicit iterators
    cout << "2. Forward iteration (explicit):\n";
    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "\n\n";

    // 4. Post-increment (post++)
    cout << "3. Post-increment iteration:\n";
    for (auto it = v1.begin(); it != v1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n\n";

    // 5. Backward iteration (pre-decrement)
    cout << "4. Backward iteration (--it):\n";
    auto it_end = v1.end();
    --it_end; // Move to last element
    while (true)
    {
        cout << *it_end << " ";
        if (it_end == v1.begin())
            break;
        --it_end;
    }
    cout << "\n\n";

    // 8. Modifying elements through iterator
    cout << "7. Modifying via iterator:\n";
    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        *it *= 2; // Double each element
    }
    for (auto val : v1)
    {
        cout << val << " ";
    }
    cout << "\n\n";

    // 9. Random access with operator[]
    cout << "8. Random access with iterator[index]:\n";
    auto it_random = v1.begin();
    cout << "it[0]=" << it_random[0] << ", it[2]=" << it_random[2] << ", it[4]=" << it_random[4] << "\n\n";

    // 10. Iterator arithmetic with + and -
    cout << "9. Iterator arithmetic (+ and -):\n";
    auto it_mid = v1.begin() + 2; // Point to 3rd element
    cout << "begin + 2: " << *it_mid << "\n";
    auto it_last = v1.end() - 1;
    cout << "end - 1: " << *it_last << "\n\n";

    // 11. Iterator += and -= operators
    cout << "10. Iterator += and -= operators:\n";
    auto it_pos = v1.begin();
    it_pos += 1;
    cout << "After += 1: " << *it_pos << "\n";
    it_pos -= 1;
    cout << "After -= 1: " << *it_pos << "\n\n";

    // 12. Comparison operators
    cout << "11. Iterator comparison:\n";
    auto it_a = v1.begin();
    auto it_b = v1.begin() + 2;
    auto it_c = v1.begin();

    cout << "it_a == it_c: " << (it_a == it_c ? "true" : "false") << "\n";
    cout << "it_a != it_b: " << (it_a != it_b ? "true" : "false") << "\n";
    cout << "\n";

    // 13. Arrow operator (->) - useful for non-trivial types
    cout << "12. Arrow operator demo (pointer iteration):\n";
    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        cout << it.operator->() << " "; // Address of current element
    }
    cout << "\n\n";

    // 14. Iterating over a vector of strings
    cout << "13. Iterator with non-trivial type (strings):\n";
    Vector<string> v_str;
    v_str.push_back("Hello");
    v_str.push_back("World");
    v_str.push_back("Iterator");

    for (auto it = v_str.begin(); it != v_str.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << "\n\n";

    // 15. Finding and modifying with iterator
    cout << "14. Find and modify pattern:\n";
    Vector<int> v2 = {1, 2, 3, 4, 5};
    for (auto it = v2.begin(); it != v2.end(); ++it)
    {
        if (*it == 3)
        {
            *it = 99;
            cout << "Found and replaced 3 with 99\n";
            break;
        }
    }
    for (auto val : v2)
    {
        cout << val << " ";
    }
    cout << "\n\n";

    // 16. Empty vector iteration
    cout << "15. Empty vector iteration:\n";
    Vector<int> v_empty;
    int count = 0;
    for (auto it = v_empty.begin(); it != v_empty.end(); ++it)
    {
        count++;
    }
    cout << "Iterations: " << count << " (should be 0)\n\n";

    // 17. Single element vector
    cout << "16. Single element vector:\n";
    Vector<int> v_single = {42};
    for (auto val : v_single)
    {
        cout << val << " ";
    }
    cout << "\n\n";

    cout << "=== All Iterator Tests Completed ===\n";

    return 0;
}
