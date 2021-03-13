#include <iostream>
#include <typeinfo>
using namespace std;

class A {
    virtual void f(){}
};

class B: public A {};
class C: public A {};

int main() {
    A *p, obja;
    B objb;
    C objc;
    int i;
    cout << "Enter 0 for A objects, ";
    cout << "1 for B objects or ";
    cout << "2 for C objects.\n";
    cin >> i;
    if (i==1)
        p = &objb;
    else if (i==2)
        p = &objc;
    else
        p = &obja;
    cout << "in object: " << typeid(*p).name() << endl;
    return 0;
}