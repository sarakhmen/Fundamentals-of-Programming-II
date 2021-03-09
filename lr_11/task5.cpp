#include <iostream>
using namespace std;

class Num{
    int num;
public:
    Num(int num): num(num) {}
    virtual void shownum() {cout << num;}
};

class outhex : public Num{
public:
    outhex(int num): Num(num) {}
    void shownum() {
        cout << hex << showbase;
        Num::shownum();
        cout << endl;
    }
};

class outoct : public Num{
public:
    outoct(int num): Num(num) {}
    void shownum() {
        cout << oct << showbase;
        Num::shownum();
        cout << endl;
    }
};


int main(){
    Num *np;
    outhex oh(128);
    outoct oo(128);
    np = &oh;
    np->shownum();
    np = &oo;
    np->shownum();
    return 0;
}