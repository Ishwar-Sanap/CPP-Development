#include <bits/stdc++.h>
using namespace std;

class B; // forward delcartion

class A
{
public:
    // shared_ptr<B> m_ptrObjB;  it will increse referece count and produce cyclic ref
    weak_ptr<B> m_ptrObjB; // weak_ptr are not incresing reference coutnt

    A()
    {
        cout << "class A constructor \n";
    }

    void set_ptr(shared_ptr<B> &ptrobjB)
    {
        m_ptrObjB = ptrobjB;
    }

    ~A()
    {
        cout << "class A Destructor \n";
    }
};

class B
{
public:
    // shared_ptr<A> m_ptrObjA; //it will increse referece count and produce cyclic ref
    weak_ptr<A> m_ptrObjA; // weak_ptr are not incresing reference coutnt

    B()
    {
        cout << "class B constructor \n";
    }
    void set_ptr(shared_ptr<A> &ptrobjA)
    {
        m_ptrObjA = ptrobjA;
    }

    ~B()
    {
        cout << "class B Destructor \n";
    }
};

int main()
{
    shared_ptr<A> ptrObjA = make_shared<A>();
    shared_ptr<B> ptrObjB = make_shared<B>();

    cout << "Ref count obj A : " << ptrObjA.use_count() << endl; // 1
    cout << "Ref count obj B : " << ptrObjB.use_count() << endl; // 1

    ptrObjB->set_ptr(ptrObjA);
    ptrObjA->set_ptr(ptrObjB);

    // To resolve the cyclic refrence dependancies weak_ptr are used..
    
    cout << "Ref count obj A : " << ptrObjA.use_count() << endl; // 1
    cout << "Ref count obj B : " << ptrObjB.use_count() << endl; // 1

    

    return 0;
}