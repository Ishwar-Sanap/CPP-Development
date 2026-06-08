#include <iostream>
#include <sstream>
#include <assert.h>
#include "String.h"
using namespace std;

/*
Requirements
    string str;          // default constructor
    string st(5, 'a');   // parameterized constructor
    string str1 = "abc"; // copy constructor
    string str2(str1);
    str1 = "xyz";                    // copy assignment
    str1 = std::move(str1);          // move assignement
    string str3 = std::move("asdf"); // move constructor

    // cin >> str1;          // take input in str1
    cout << str1 << endl; // print output string

    str1 += str2; // appends str2 in str1

    // methods
    str.push_back('p');
    str.pop_back();
    str.length(); // str.size();
    str.capacity();
    str.find('a');
    // str.substr(1, 3); // starting from 1st index 3 length substring
    str.clear();

    cout << str1 << endl;
    str1 += str1;
    cout << str1 << endl;

*/

int main()
{
    String empty1 = "";

    String str = "abcd"; // copy constructor
    String st(5, 'a');

    cout << "string st : " << st << " length : " << st.length() << endl;
    cout << "string str : " << str << " length : " << str.length() << endl;

    cout << str[2] << endl;

    str.push_back('e');
    str.push_back('f');

    str.pop_back();

    cout << str << endl;

    str = st; // copy assignment

    cout << str << endl;

    str = "ABCDE";

    String str2 = "Hello";
    str2 += " World";
    cout << str2 << endl;

    const String s1 = "SampleSize";

    cout << s1[2] << endl;
    cout << s1 << endl;

    /*Edge Cases Handling*/
    String empty;
    String empty2 = "";
    assert(empty == empty2);
    assert(empty.size() == 0);
    cout << "empty string: '" << empty << "' size=" << empty.size() << " cap=" << empty.capacity() << "\n";

    String a = "abcd";
    String b(5, 'x');
    cout << "a=" << a << " b=" << b << "\n";

    String c = a + b;
    assert(c == String("abcdxxxxx"));
    cout << "a + b = " << c << "\n";

    a += "123";
    assert(a == String("abcd123"));
    cout << "a += \"123\" -> " << a << "\n";

    String d = empty + a;
    String e = a + "";
    String f = empty + empty;
    assert(d == a);
    assert(e == a);
    assert(f == empty);
    cout << "empty + a = " << d << "\n";

    String moved = std::move(b);
    assert(moved == String("xxxxx"));
    cout << "moved = " << moved << "\n";
    cout << "source after move size=" << b.size() << " data='" << b << "'\n";

    moved.clear();
    assert(moved.size() == 0);
    cout << "moved after clear: '" << moved << "' size=" << moved.size() << "\n";

    String input;
    istringstream iss("hello_world");
    iss >> input;
    assert(input == String("hello_world"));
    cout << "istream input: '" << input << "'\n";

    String pushPop;
    pushPop.push_back('q');
    pushPop.push_back('r');
    assert(pushPop == String("qr"));
    pushPop.pop_back();
    assert(pushPop == String("q"));
    pushPop.pop_back();
    assert(pushPop.size() == 0);
    cout << "push/pop edge case ok" << "\n";

    cout << "All String checks passed.\n";

    return 0;
}