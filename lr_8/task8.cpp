#include <iostream>

using namespace std;
class A {
    int i;
public:
    A(int a) { i = a; }
};

class B {
    int j;
public:
    B(int a) { j = a; }
};

class C : public A, public B {
    int k;
public:
    C(int i, int j, int k): A(i), B(j), k(k) {}
};

int main(){
    C obj(1, 2, 3);
    return 0;
}
