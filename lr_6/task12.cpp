#include <iostream>
using namespace std;

class samp {
    int a;
public:
    samp(){ a = 0; }
    samp(int val) { a = val; }
    int get_a() { return a; }
};


int main() {
    samp obj(88);
    samp objarray[10];
    cout << "obj = " << obj.get_a() << endl;
    cout << "objarray = ";
    for(int i = 0; i < 10; ++i)
        cout << objarray[i].get_a() << ' ';
    cout << endl;
}