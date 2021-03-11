#include <iostream>
using namespace std;

template <class T>
T abs(T val){
    return val < 0 ? -val: val;
}

int main(){
    cout << "abs(-5) = " << abs(-5) << endl;
    cout << "abs(-10.3) = " << abs(-10.3) << endl;
    return 0;
}