#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    cout << hex;
    cout << setiosflags(ios::showbase) << 100 << endl;
    return 0;
}