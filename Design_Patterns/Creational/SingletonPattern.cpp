#include <bits/stdc++.h>
using namespace std;

// Singleton Class make sure that, ther is only one instace exist through out the programme

class Test
{
private:
   static Test *m_ptrTestObj; // declaration
   // making constructor private so from outside instance can't be created..
   Test() {}
   ~Test() {}

   // Delete copy constructor & assignment operator
   Test(const Test &) = delete;
   Test &operator=(const Test &) = delete;

public:
   static Test *getTestInstance()
   {
      // if 2 threds simaltanenously called this method first time 
      //then might be 2 objects can be created..
      if (!m_ptrTestObj)
      {
         m_ptrTestObj = new Test();
      }

      return m_ptrTestObj;
   }

   static void deleteTestInstance()
   {
      delete m_ptrTestObj;
      m_ptrTestObj = nullptr;
   }
};

// only static members must be defined outside of the class
Test *Test::m_ptrTestObj = nullptr; // defination + initialization

/********************* Modern Approach thread safe  ******************* */
class Test2
{
private:
   Test2() {}

   //Delete Copy constructor and copy assignment operator
   Test2(const Test2 &) = delete;
   Test2 &operator=(const Test2 &) = delete;

public:
   static Test2 &getTest2Instance()
   {
      static Test2 Test2Obj; // created once & thread safe
      return Test2Obj;       // return reference of static local object
   }
};
int main()
{

   Test *t1 = Test::getTestInstance();
   Test *t2 = Test::getTestInstance();

   // Both the instance have same address
   cout << t1 << " " << t2 << endl;

   // At programme termination delete the object
   Test::deleteTestInstance();

   Test2 &obj1 = Test2::getTest2Instance();
   Test2 &obj2 = Test2::getTest2Instance();

   cout << &obj1 << " " << &obj2 << endl;

   return 0;
}