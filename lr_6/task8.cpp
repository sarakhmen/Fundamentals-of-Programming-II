#include <iostream>
using namespace std;

int dif(int a, int b){
    return a-b;
}

float dif(float a, float b){
    return a-b;
}

int main(){
    int (*p1)(int, int);
    float (*p2)(float, float);
    p1 = dif;
    p2 = dif;
    cout << "(int)dif between 10 and 12 = " << p1(10, 12) << endl;
    cout << "(float)dif between 10.1 and 12.2 = " << p2(10.1, 12.2) << endl;
    return 0;
}