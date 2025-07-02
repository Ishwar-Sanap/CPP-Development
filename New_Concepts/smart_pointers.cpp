#include <iostream>
#include <memory>
using namespace std;

// Why we need of smart pointers??
/*
    -   For below f1() function if blok condition becomes true then it will return from the function
        so, the dyncamically allocated memory for ptr is not deleted, and there will be memory leak's

    -  To avoid manual delete and allocate of dynamic memory we can use smart pointers to avoid
         - memory leaks, dangling pointers.

*/
int f1(int k)
{
    int *ptr = new int(10);

    if (k == 1)
        return -1;

    delete ptr;
    ptr = nullptr;
}

int f2(int k)
{
    // Two ways to create the smart pointer obj

    unique_ptr<int> pObj(new int(10));

    // make_unique is a function template returns the unique_ptr<> and Exception safe
    unique_ptr<int> pObj2 = make_unique<int>(10);

    if (k == 1)
        return -1; // even though, function return from here allocated memory for resources are safely deleted

    cout << pObj2.get() << endl; // return the stored pointer

    // The deleter will be invoked if a pointer is already owned. and Replace the stored pointer with new address.
    pObj2.reset(new int(20));

    pObj2.release(); // Release ownership of any stored pointer.

    // when pObj goes out of scope it will call the destructor and release the resorces

    // pObj is class object but it work like smart pointer
    // Smart pointers overload common pointer operators like * and ->,
    // so you can access the managed object just like you would with raw pointers.

    cout << *(pObj) << endl;
}

class Test
{
public:
    Test()
    {
        std::cout << "Test Constructor\n";
    }
    ~Test()
    {
        std::cout << "Test Destructor\n";
    }

    void greet()
    {
        std::cout << "Hello from Test\n";
    }
};

int main()
{
    f2(2);

    /********************* unique_ptr ******************** */

    // unique_ptr<Test> ptrTestObj1(new Test()); //if constructor throws, memory leaks
    // If the constructor throws after allocation, new MyClass() leaks memory since unique_ptr hasn’t taken ownership yet.

    unique_ptr<Test> ptrTestObj = make_unique<Test>(); // safe even if constructor throws Error

    ptrTestObj->greet();

    // copy of constructor and copy assignment are not allowed
    //  unique_ptr<Test>ptrTestObj2 = ptrTestObj;

    // move constructor is applicable to transfer the owernship
    unique_ptr<Test> ptrTestObj2 = move(ptrTestObj); // move will covert lvalue to Rvalue

    ptrTestObj2->greet();

    if (ptrTestObj) // ptrTestObj is no longer owerner of resource
        ptrTestObj->greet();

    cout<< "\n*************************************************************\n";
    /************************************************************* */

    /********************* shared_ptr ***************************** */

    /*
        -   A shared pointer is a container for raw pointer
        -   It maintains reference counting owernship of it's contained pointer
            in cooperation with all copies of the shared_ptr
        -   The resource referenced by the contained raw pointer will be deleted when and
            only when all copies of the shared_ptr have been destroyed (i.e reference count becomes 0)
    */
    shared_ptr<Test> ptrTestSh1 = make_shared<Test>();

    shared_ptr<Test> ptrTestSh2(ptrTestSh1); // copy consructor is allowed

    shared_ptr<Test> ptrTestSh3;

    ptrTestSh3 = ptrTestSh2; // copy assignemtn is allowed

    cout << "Sh1 -> " << ptrTestSh1.get() << " Sh2 -> " << ptrTestSh2.get() << " Sh3 -> " << ptrTestSh3.get() << endl;
    cout << "Ref count of resource : " << ptrTestSh1.use_count() << endl; // 3

    ptrTestSh1.reset(); // ptrTestSh1 no longer owern of the shared resource

    cout << "Sh1 -> " << ptrTestSh1.get() << " Sh2 -> " << ptrTestSh2.get() << " Sh3 -> " << ptrTestSh3.get() << endl;
    cout << "Ref count of resource : " << ptrTestSh2.use_count() << endl; // 2

    ptrTestSh3 = move(ptrTestSh2); // move ownership to ptrTestSh3

    cout << "Sh1 -> " << ptrTestSh1.get() << " Sh2 -> " << ptrTestSh2.get() << " Sh3 -> " << ptrTestSh3.get() << endl;
    cout << "Ref count of resource : " << ptrTestSh3.use_count() << endl; // 1

    /************************************************************* */
    cout<< "\n*************************************************************\n";

    /********************* weak_ptr ***************************** */

    //  weak pointer always points to only shared pointers
    // It doesn't Increase or decrease the reference count of shared resources

    cout << "Ref count of resource : " << ptrTestSh3.use_count() << endl; // 1

    weak_ptr<Test> ptrTestWk1 = ptrTestSh3;

    /*
        weak_ptr<Test> ptrTestWk1 = move(ptrTestSh3);

        weak_ptr doesn’t "take" ownership
        ptrTestSh3 still holds the resource
        ptrTestSh3.use_count() remains the same (just observed)
    */
    
    cout << "Ref count of resource : " << ptrTestSh3.use_count() << endl; // 1
    
    ptrTestWk1.lock()->greet(); // to access the resource we have to use lock() -->  convert to shared_ptr safely
    
    ptrTestWk1.reset();

    cout << "Ref count of resource : " << ptrTestSh3.use_count() << endl; // 1
    
    return 0;
}