#include <iostream>
using namespace std;

class base{
    int a;
public:
    void load_a(int n ){ a = n;}
    int get_a(){ return a;}
};

class derived: public base{
    int b;
public:
    void load_b(int n) { b = n ;}
    int get_b() {return b;}
};

int main(){
    derived test1;
    derived test2;
    test1.load_a(1);
    test1.load_b(2);
    cout << "<test2 = test1>" << endl;
    test2 = test1;
    cout << "test1 content:" << endl;
    cout << "a = " << test1.get_a() << "; b = " << test1.get_b() << endl;
    cout << "test2 content:" << endl;
    cout << "a = " << test2.get_a() << "; b = " << test2.get_b() << endl;
    return 0;
}