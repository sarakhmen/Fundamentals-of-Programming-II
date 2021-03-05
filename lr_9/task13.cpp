#include <iostream>

using namespace std;

int main(){
    cout << 100 << endl;
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << 100 << endl;
    cout.unsetf(ios::hex);
    cout.setf(ios::oct);
    cout << 100 << endl;
    return 0;
}