#include <iostream>

using namespace std;

template <class T>
T sum_of_elements(T *arr, int size){
    T sum = {};
    for(int i = 0; i < size; ++i)
        sum = sum + arr[i];
    return sum;
}

int main(){
    double arr[10] = { 0.4, 10, 23.5, 2.444, 123, 442.5, 3.1123, 42.1239, 90.1, 0};
    cout << "sum of elements = " << sum_of_elements(arr, 10) << endl;
    return 0;
}