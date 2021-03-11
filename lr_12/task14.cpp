#include <iostream>
#include <exception>
using namespace std;

const int SIZE{10};

template<class T>
class arraytype{
    T a[SIZE];
public:
    arraytype(){
        for(int i = 0; i < SIZE; ++i)
            a[i] = T{};
    }
    T &operator [](int i){
        if(i < 0 || i >= SIZE)
            throw out_of_range("Your index is out of bounds");
        return a[i];
    }
};


int main(){
    arraytype<double> arr;
    try{
        arr[20] = 4.5;
    }
    catch(out_of_range &e){
        cout << e.what();
    }
    return 0;
}