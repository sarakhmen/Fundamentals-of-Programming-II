#include <iostream>
using namespace std;

template <class T>
void my_swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void bubble_sort(T *arr, int size){
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size-i-1; ++j)
            if(arr[j] > arr[j+1])
                my_swap(arr[j], arr[j+1]);
}

int main(){
    int arr[20];
    for(int i = 0; i < 20; ++i)
        arr[i] = 20 - i;
    cout << "original arr: ";
    for(int i = 0; i < 20; ++i)
        cout << arr[i] << ' ';
    cout << endl;
    bubble_sort(arr, 20);
    cout << "sorted arr: ";
    for(int i = 0; i < 20; ++i)
        cout << arr[i] << ' ';
    return 0;
}