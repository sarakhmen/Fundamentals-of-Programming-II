#include <iostream>
using namespace std;

class three_d {
    int x, y, z;
public:
    three_d(int i, int j, int k) { x=i; y=j; z=k; }
    three_d(){ x=0; y=0; z=0; }
    void get(int &i, int &j, int &k) { i=x; j=y; k=z; }
    three_d operator +(three_d);
    three_d operator -(three_d);
    three_d &operator --();
    three_d &operator ++();
};

three_d three_d::operator +(three_d obj){
    obj.x += x;
    obj.y += y;
    obj.z += z;
    return obj;
}

three_d three_d::operator -(three_d obj){
    obj.x = x - obj.x;
    obj.y = y - obj.y;
    obj.z = z - obj.z;
    return obj;
}

three_d &three_d::operator --(){
    --x;
    --y;
    --z;
    return *this;
}

three_d &three_d::operator ++(){
    ++x;
    ++y;
    ++z;
    return *this;
}

int main(){
    three_d obj(5, 4, 3), obj2(4, 3, 2);
    int x, y, z;
    obj.get(x, y, z);
    cout << "obj: X = " << x << ", Y = " << y << ", Z = " << z << endl;
    obj2.get(x, y, z);
    cout << "obj2: X = " << x << ", Y = " << y << ", Z = " << z << endl;
    obj = obj - obj2;
    obj.get(x, y , z);
    cout << "obj - obj2 : X = " << x << ", Y = " << y << ", Z = " << z << endl;
    obj = obj2 + obj2;
    obj.get(x, y , z);
    cout << "obj2 + obj2 : X = " << x << ", Y = " << y << ", Z = " << z << endl;
    ++obj2;
    obj2.get(x, y , z);
    cout << "++obj2 : X = " << x << ", Y = " << y << ", Z = " << z << endl;
    --obj2;
    obj2.get(x, y , z);
    cout << "--obj2 : X = " << x << ", Y = " << y << ", Z = " << z << endl;
    return 0;
}