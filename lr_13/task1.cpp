#include <iostream>
using namespace std;

template <class T>
class coord {
    T x, y;
public:
    coord() {x = T{}; y = T{};}
    coord(T i, T j) { x = i; y = j;}
    void get_xy(T &i, T &j) {i = x; j = y;}
    coord<T> operator +(const coord<T> obj);
};

template <class T>
coord<T> coord<T>::operator +(const coord<T> obj){
    coord<T> temp;
    temp.x = x + obj.x;
    temp.y = y + obj.y;
    return temp;
}

int main(){
    coord<int> obj1(10, 10), obj2(5, 3), obj3;
    int x, y;
    obj3 = obj1 + obj2;
    obj3.get_xy(x, y);
    cout << "(obj1+obj2) X: " << x << ", Y: " << y << endl;
    return 0;
}