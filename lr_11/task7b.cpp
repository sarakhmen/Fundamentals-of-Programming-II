#include <iostream>
using namespace std;

class base {
public:
	virtual void func(){
        cout << "Using base version of func()\n";
    }
};

class derived1: public base {
public:
	// void func(){
    //     cout << "Using derived1 version of func()\n";
    // }
};

class derived2: public derived1 {
public:
	// void func(){
    //     cout << "Using derived2 version of func()\n";
    // }
};

int main () {
    base *p;
    derived2 obj;
    p = &obj;
    p->func();
	return 0;
}