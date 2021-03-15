#include <iostream>
using namespace std;

class A{
    int value;
public:
    A(int v): value(v) {}
    int &get(){return value;}
    void do_smthng() const{
        cout << "trying to test behavior, so im incrementing value withing const func" << endl;
        cout << "original value = " << value << endl;
        const_cast<A *>(this)->value++;
        cout << "incremented value = " << value << endl;
    }
};

int main(){
    A obj(10);
    obj.do_smthng();
    return 0;
}