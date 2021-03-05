#include <iostream>
using namespace std;

class pwr {
    int base;
    int exponent;
    double result; // base to the exponent power
public:
    pwr(int b, int e); 
    friend ostream &operator <<(ostream &stream, pwr &obj); 
    friend istream &operator >>(istream &stream, pwr &obj);
};

pwr::pwr(int b, int e) {
    base = b;
    exponent = e;
    result = 1;
    for ( ; e; e--)
        result = result * base;
}

ostream &operator <<(ostream &stream, pwr &obj){
    stream << "base: " << obj.base << endl;
    stream << "exponent: " << obj.exponent << endl;
    stream << "result: " << obj.result  << endl;
    return stream;
}

istream &operator >>(istream &stream, pwr &obj){
    stream >> obj.base >> obj.exponent;
    obj.result = 1;
    int e = obj.exponent;
    for ( ; e; e--)
        obj.result = obj.result * obj.base;
    return stream;
}

int main(){
    pwr obj1(10, 2);
    cout << "Your object:\n" << obj1;
    cout << "\nEnter base and exponent: ";
    cin >> obj1;
        cout << "Your new object:\n" << obj1;
}