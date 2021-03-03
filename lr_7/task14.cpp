#include <iostream>
using namespace std;


class coord {
    int x, y;
public:
    coord() {x = 0; y = 0;}
    coord(int i, int j) { x = i; y = j;}
    void get_xy(int &i, int &j) {i = x; j = y;}
    coord operator >>(int);
    coord operator <<(int);
};

coord coord::operator <<(int k){
    coord temp;
    temp.x = x << k;
    temp.y = y << k;
    return temp;
}

coord coord::operator >>(int k){
    coord temp;
    temp.x = x >> k;
    temp.y = y >> k;
    return temp;
}


int main(){
    coord obj1(2, 2);
    int x, y;
    obj1 = obj1 << 2;
    obj1.get_xy(x, y);
    cout << "obj1(2, 2) << 2 : X = " << x << ", Y = " << y << endl;
    obj1 = obj1 >> 2;
    obj1.get_xy(x, y);
    cout << "obj1(8, 8) >> 2 : X = " << x << ", Y = " << y << endl;
    return 0;
}