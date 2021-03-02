#include <iostream>
#include <cmath>
using namespace std;

class coord {
    int x, y;
public:
    coord() {x = 0; y = 0;}
    coord(int i, int j) { x = i; y = j;}
    void get_xy(int &i, int &j) {i = x; j = y;}
    bool operator <(const coord &obj);
    bool operator >(const coord &obj);
};

bool coord::operator >(const coord &obj){
    return sqrt(x*x + y*y) > sqrt(obj.x*obj.x + obj.y*obj.y);
}

bool coord::operator <(const coord &obj){
    return sqrt(x*x + y*y) < sqrt(obj.x*obj.x + obj.y*obj.y);
}


int main(){
    coord obj1(10, 10), obj2(20, 20);
    cout << "obj1(10, 10) < obj2(20, 20) = " << (obj1 < obj2) << endl;
    cout << "obj1(10, 10) > obj2(20, 20) = " << (obj1 > obj2) << endl;
    return 0;
}