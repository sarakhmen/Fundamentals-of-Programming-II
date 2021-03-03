#include <iostream>
using namespace std;

class dynarray{
    int *ptr;
    int size;
public:
    dynarray(int s);
    ~dynarray(){delete ptr;}
    int &put(int i);
    int get(int i);
    dynarray &operator =(dynarray &arr);
};

dynarray::dynarray(int s){
    if(s<0) exit(1);
    ptr = new int[s]{};
    if(!ptr) exit(1);
    size = s;
}

int &dynarray::put(int i){
    if(i < 0 || i >= size){
        cout << "Bounds error!" << endl;
        exit(1);
    }    
    return ptr[i];
}

int dynarray::get(int i){
    if(i < 0 || i >= size){
        cout << "Bounds error!" << endl;
        exit(1);
    }    
    return ptr[i];
}

dynarray &dynarray::operator=(dynarray &arr){
    if(size < arr.size){
        delete ptr;
        ptr = new int[arr.size];
        if(!ptr) exit(1);
    }
    for(int i = 0; i < arr.size; ++i)
        ptr[i] = arr.ptr[i];
    size = arr.size;
    return *this; 
}


int main(){
    dynarray arr1(10), arr2(20);
    for(int i = 0; i < 10; ++i)
        arr1.put(i) = i;
    cout << "arr1 = ";
    for(int i = 0; i < 10; ++i)
        cout << arr1.get(i) << " ";
    cout << endl;
    arr1 = arr2;
    cout << "arr1 = arr2" << endl;
    cout << "arr1 = ";
    for(int i = 0; i < 20; ++i)
        cout << arr1.get(i) << " ";
    cout << endl;
    return 0;
}

