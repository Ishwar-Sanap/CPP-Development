
/*
Requirements for Vector Class

Vector<int> vt; //default constructor
Vector<int> vt1(n, 0); // parameterized constructor
Vector<int> vt1(n); // parameterized constructor
Vector<int> vt2 = {1,2,4}; // constructor with initilizer list
Vector<int> vt3 = vt2; // copy constructor
vt1 = vt2; // copy assignment
Vector<int>vt4 = move(vt1); move constructor
vt3 = move(vt1); move assignment

int ele = v1[0];
v1[0] = 10;
vt.at(-1); // should throws out of bound
vt.assign(n, 0);
vt.resize(n)
vt.resize(n,0)
vt.size();
vt.capacity();
vt.push_back();
vt.pop_back();
vt.clear();

*/

#include <iostream>
#include "Vector.h" //custom vector class
using namespace std;

void printVector(Vector<int> &vt)
{
    for (int i = 0; i < vt.size(); i++)
        cout << vt[i] << " ";

    cout << endl;
}
int main()
{

    Vector<int> v1;
    v1.push_back(11);
    v1.push_back(21);
    v1.push_back(51);

    printVector(v1);

    cout << "Vector size : " << v1.size() << endl;
    cout << "Vector Capacity : " << v1.capacity() << endl;

    Vector<int> v2 = {1, 2, 3};

    printVector(v2);

    v2[1] = 22;
    printVector(v2);

    cout << v2.at(1) << endl;
    // cout << v2.at(-1) << endl;  throw exception 'std::out_of_range' what():  Vector element access out of range
    // cout << v2[-1] << endl;  no exception but return garbage value for out of bound address

    v1 = std::move(v2);

    printVector(v1);
    cout << "Vector2 size : " << v2.size() << endl;
    cout << "Vector2 Capacity : " << v2.capacity() << endl;

    v1.reserve(10);
    printVector(v1);
    v1.resize(6);
    printVector(v1);

    v1.clear();
    printVector(v1);

    // Edge case tests for robustness
    cout << "\n--- Edge Case Tests ---\n";

    // 1. Empty vector operations
    Vector<int> emptyVec;
    cout << "Empty vector size: " << emptyVec.size() << ", capacity: " << emptyVec.capacity() << endl;
    try {
        // front/back on empty should ideally throw or handle, but current impl may crash
        // cout << "front: " << emptyVec.front() << endl; // Uncomment to test crash
        // cout << "back: " << emptyVec.back() << endl;   // Uncomment to test crash
    } catch (const std::exception& e) {
        cout << "Exception on empty access: " << e.what() << endl;
    }

    // 2. pop_back on empty
    emptyVec.pop_back(); // Should do nothing
    cout << "pop_back on empty: size=" << emptyVec.size() << endl;

    // 3. clear on empty
    emptyVec.clear();
    cout << "clear on empty: size=" << emptyVec.size() << endl;

    // 4. Empty initializer list
    Vector<int> emptyInit = {};
    cout << "Empty init list: size=" << emptyInit.size() << endl;

    // 5. resize to 0
    Vector<int> v3 = {1, 2, 3};
    v3.resize(0);
    cout << "resize to 0: size=" << v3.size() << ", capacity=" << v3.capacity() << endl;

    // 6. resize to larger than capacity
    v3.resize(10);
    cout << "resize to 10: size=" << v3.size() << ", capacity=" << v3.capacity() << endl;
    printVector(v3);

    // 7. reserve smaller or same
    v3.reserve(5); // Should do nothing since 10 > 5
    cout << "reserve(5) on capacity 10: capacity=" << v3.capacity() << endl;
    v3.reserve(15);
    cout << "reserve(15): capacity=" << v3.capacity() << endl;

    // 8. at with negative index
    try {
        cout << v3.at(-1) << endl;
    } catch (const std::out_of_range& e) {
        cout << "at(-1) exception: " << e.what() << endl;
    }

    // 9. operator[] out of bounds (no exception, undefined behavior)
    // cout << v3[100] << endl; // Uncomment to test potential crash/garbage

    // 10. Self copy assignment
    Vector<int> v4 = {4, 5, 6};
    v4 = v4; // Self-assignment
    cout << "Self copy assignment: ";
    printVector(v4);

    // 11. Move from moved-from object
    Vector<int> v5 = std::move(v4);
    cout << "After move: v4 size=" << v4.size() << ", v5 size=" << v5.size() << endl;
    // Move from moved-from (should be safe, like assigning nullptr)
    Vector<int> v6 = std::move(v4);
    cout << "Move from moved-from: v4 size=" << v4.size() << ", v6 size=" << v6.size() << endl;

    // 12. Copy constructor from empty
    Vector<int> v7 = emptyVec;
    cout << "Copy from empty: v7 size=" << v7.size() << endl;

    // 13. Large resize (if memory allows)
    // v3.resize(1000000); // Uncomment for large test, but may fail

    cout << "\n--- All tests completed ---\n";

    return 0;
}