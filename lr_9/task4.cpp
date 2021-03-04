#include <iostream>
using namespace std;

int main(){
    ios_base::fmtflags prev_state = cout.flags();
    cout.unsetf(ios::dec);
    cout.setf(ios::showbase | ios::hex);
    cout << 100 << endl;
    cout.setf(prev_state);
    cout << 100 << endl;
    return 0;
}