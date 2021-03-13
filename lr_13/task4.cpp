#include <iostream>
using namespace std;

void f(const double &i) {
    *const_cast<double*>(&i) = 100;
}

void f2(const int &i){
    *const_cast<int*>(&i) = 100;
    cout << i;
}

int main() {
    double x = 98.6;
    cout << x << endl;
    f(x);
    cout << x << endl;
    f2(10);
    return 0;
}
