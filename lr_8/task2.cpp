#include <iostream>

using namespace std;

class Array{
    int nums[10];
public:
    Array();
    void set(int n[10]);
    void show();
    friend Array operator +(Array obj1, Array obj2);
    friend Array operator -(Array obj1, Array obj2);
    friend bool operator ==(Array obj1, Array obj2);
};

Array operator +(Array obj1, Array obj2){
    Array temp;
    for (int i=0; i <10; i++) 
        temp.nums[i] = obj1.nums[i] + obj2.nums[i];
    return temp;
}

Array operator -(Array obj1, Array obj2){
    Array temp;
    for (int i=0; i <10; i++) 
        temp.nums[i] = obj1.nums[i] + obj2.nums[i];
    return temp;
}

bool operator ==(Array obj1, Array obj2){
    for (int i=0; i <10; i++) 
        if(obj1.nums[i] != obj2.nums[i])
            return false;
    return true;
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
    Array obj1, obj2, obj3;
    int i[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9 ,10};
    obj1.set(i);
    obj2.set(i);
    obj3 = obj1 + obj2;
    obj3.show();
    obj3 = obj1 - obj3;
    obj3. show();
    if (obj1 == obj2)
        cout << "obj1 equals obj2\n";
    else
        cout << "obj1 does not equal obj2\n";
    if (obj1 == obj3)
        cout << "obj1 equals obj3\n";
    else
        cout << "obj1 does not equal obj3\n";
    return 0;
}