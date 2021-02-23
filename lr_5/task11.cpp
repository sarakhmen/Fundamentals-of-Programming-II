#include <iostream>
using namespace std;

void neg(int *value){
    *value = -*value;
}

void neg(int &value){
    value = -value;
}

int main(){
    int num = 13;
    cout << "our int value = " << num << endl;
    neg(&num);
    cout << "the previous value taken with the opposite sign through a pointer = " << num << endl;
    neg(num);
    cout << "the previous value taken with the opposite sign through a reference = " << num << endl; 
    return 0;
}