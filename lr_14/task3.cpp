#include <iostream>
#include <cmath>
using namespace std;

class Pwr {
    int base;
    int exp;
public:
    Pwr(int b, int e) { base = b; exp = e; }
    operator int(){
        return pow(base, exp);
    }
};


int main(){
    Pwr obj(7, 2.5);
    cout << obj;
    return 0;
}