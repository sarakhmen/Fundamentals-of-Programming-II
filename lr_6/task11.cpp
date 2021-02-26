#include <iostream>
using namespace std;

void order(int &a, int &b){
    if(a>b){
        int temp = a;
        a = b;
        b = temp;
    }
}

int main(){
    int x = 12,
        y = 10;
    cout << "x = " << x << ", y = " << y << endl;
    order(x, y);
    cout << "\t<order(x, y)>" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    order(x, y);
    cout << "\t<order(x, y)>" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    return 0;
}