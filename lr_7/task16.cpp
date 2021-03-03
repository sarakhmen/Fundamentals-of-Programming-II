#include <iostream>
using namespace std;

class three_d {
    int x, y, z;
public:
    three_d(int i, int j, int k) { x=i; y=j; z=k; }
    three_d(){ x=0; y=0; z=0; }
    void get(int &i, int &j, int &k) { i=x; j=y; k=z; }
    three_d operator +(three_d &);
    three_d operator -(three_d &);
    bool operator ==(three_d &);
    bool operator !=(three_d &);
    bool operator ||(three_d &);
    friend three_d &operator --(three_d &);
    friend three_d &operator ++(three_d &);
    friend three_d operator +(three_d &, int);
    friend three_d operator +(int, three_d &);
};

three_d operator +(three_d &obj, int val){
    three_d temp;
    temp.x = obj.x + val;
    temp.y = obj.y + val;
    temp.z = obj.z + val;
    return obj;
}

three_d operator +(int val, three_d &obj){
    three_d temp;
    temp.x = obj.x + val;
    temp.y = obj.y + val;
    temp.z = obj.z + val;
    return obj;
}

bool three_d::operator ==(three_d &obj){
    return x==obj.x && y==obj.y && z==obj.z;
}

bool three_d::operator !=(three_d &obj){
    return !(x==obj.x && y==obj.y && z==obj.z);
}

bool three_d::operator ||(three_d &obj){
    return (x||obj.x) || (y||obj.y) || (z||obj.z);
}

three_d three_d::operator +(three_d &obj){
    three_d temp;
    temp.x = x + obj.x;
    temp.y = y + obj.y;
    temp.z = z + obj.z;
    return temp;
}

three_d three_d::operator -(three_d &obj){
    three_d temp;
    temp.x = x - obj.x;
    temp.y = y - obj.y;
    temp.z = z - obj.z;
    return temp;
}

three_d &operator --(three_d &obj){
    --obj.x;
    --obj.y;
    --obj.z;
    return obj;
}

three_d &operator ++(three_d &obj){
    ++obj.x;
    ++obj.y;
    ++obj.z;
    return obj;
}

int main(){

    return 0;
}