#include <iostream>

using namespace std;

int main(){
    cout.width(20);
    cout.fill('*');
    cout.precision(2);
    cout.setf(ios::left | ios::fixed);
    cout << 1000.5364 << endl;
    return 0;
}