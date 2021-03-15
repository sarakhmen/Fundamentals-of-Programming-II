#include <iostream>
using namespace std;

class A{
    static int counter;
public:
    A(){ 
        ++counter; 
        cout << "constructing, counter = " << counter << endl;
    }
    ~A() {
        --counter; 
        cout << "destructing, counter = " << counter << endl;
    }
};
int A::counter = 0;


int main(){
    A arr[10];
    return 0;
}
