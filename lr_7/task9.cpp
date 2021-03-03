#include <iostream>
using namespace std;

class my_class{
    int x;
public:
    my_class() { x = 0;}
    my_class(int i) { x = i;}
    int &get() {return x;}
    friend my_class &operator ++(my_class &);
    friend my_class operator ++(my_class &, int);
};

my_class &operator ++(my_class &obj){
    ++obj.get();
    return obj;
}

my_class operator ++(my_class &obj, int){
    return obj.get()++;
}


int main(){
    my_class obj(10);
    cout << "Initial value = " << obj.get() << endl;
    cout << "++obj value = " << (++obj).get() << endl;
    cout << "obj++ value = " << (obj++).get() << endl;
    cout << "final value = " << obj.get() << endl;
    return 0;
}


