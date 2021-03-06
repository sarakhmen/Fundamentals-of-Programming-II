#include <iostream>
using namespace std;

ostream &sethex(ostream &stream){
    return stream << hex << uppercase << showbase;
}

ostream &reset(ostream &stream){
    return stream << dec << nouppercase << noshowbase;
}

int main(){
    cout << sethex << 100 << endl;
    cout << reset << 100 << endl;
    return 0;
}