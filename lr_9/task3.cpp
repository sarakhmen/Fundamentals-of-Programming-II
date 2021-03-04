#include <iostream>
using namespace std;

int main(){
    cout.setf(ios::showpoint | ios::scientific | ios::uppercase);
    cout << 100000.0 << endl;
    return 0;
}