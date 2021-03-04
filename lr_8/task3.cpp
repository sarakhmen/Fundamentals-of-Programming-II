#include <iostream>

using namespace std;

class Array{
    int nums[10];
public:
    Array();
    void set(int n[10]);
    void show();
    Array &operator ++();
    friend Array operator -(Array &obj);
};

Array operator -(Array &obj){
    Array temp;
    for (int i=0; i <10; i++) 
        temp.nums[i] = -obj.nums[i];
    return temp;
}

Array &Array::operator ++(){
    for (int i=0; i <10; i++) 
        ++nums[i];
    return *this;
}

Array::Array() {
    for (int i=0; i <10; i++) nums[i] = 0;
}
void Array::set(int *n) {
    for (int i=0; i<10; i++) nums[i] = n[i];
}
void Array::show() {
    for (int i=0; i<10; i++)
    cout << nums[i] << ' ';
    cout << "\n";
}
// Fill in operator functions.
int main() {
    Array obj1;
    int i[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9 ,10};
    obj1.set(i);
    obj1.show();
    obj1 = -obj1;
    obj1.show();
    ++obj1;
    obj1.show();
    return 0;
}