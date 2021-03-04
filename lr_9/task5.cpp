#include <iostream>
#include <cmath>
using namespace std;

int main(){
    cout.precision(5);
    cout.setf(ios::right | ios::fixed);
    cout.width(10);
    cout << "x";
    cout.width(10);
    cout << "log(x)";
    cout.width(10);
    cout << "log10(x)" << endl;
    for(int i = 2; i < 101; ++i){
        cout.width(10);
        cout << i;
        cout.width(10);
        cout << log(i);
        cout.width(10);
        cout << log10(i) << endl;
    }
    return 0;
}