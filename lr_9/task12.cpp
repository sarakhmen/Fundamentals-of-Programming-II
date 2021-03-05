#include <iostream>
#include <cmath>
using namespace std;

class my_int{
    int val;
    int min_div;
    public:
    my_int(){val = 0; min_div = 0;}
    friend ostream &operator<<(ostream &stream, my_int &obj);
    friend istream &operator>>(istream &stream, my_int &obj);
};

ostream &operator<<(ostream &stream, my_int &obj){
    stream << "Int: " << obj.val << endl;
    stream << "Lowest divisor: " << obj.min_div << endl;
    return stream;
}

istream &operator>>(istream &stream, my_int &obj){
    stream >> obj.val;
    if(obj.val == 0)
        obj.min_div = 0;
    obj.min_div = 1;
    for(int i = 2; i < abs(obj.val); ++i){
        if(obj.val % i == 0){
            obj.min_div = i;
            break;
        }
    }
    return stream;
}


int main(){
    my_int num;
    cout << "Enter your number: ";
    cin >> num;
    cout << num;
    return 0;
}