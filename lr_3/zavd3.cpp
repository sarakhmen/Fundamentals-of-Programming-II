#include <iostream>
using namespace std;

union bits{
    int value;
    unsigned char bytes[sizeof(int)];
};

int main(){
    bits bt;
    unsigned char temp;
    bt.value = 321;
    cout << "Integer = " << bt.value << endl;
    temp = bt.bytes[sizeof(int)-1];
    bt.bytes[sizeof(int)-1] = bt.bytes[0];
    bt.bytes[0] = temp;
    cout << "Integer with swapped low and high bytes = " << bt.value << endl;
    bt.bytes[0] = bt.bytes[sizeof(int)-1];
    bt.bytes[sizeof(int)-1] = temp;
    cout << "Integer with swapped back low and high bytes = " << bt.value << endl;
    return 0;
}