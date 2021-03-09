#include <iostream>
using namespace std;

template <class T>
int fInd(T object, T *list, int size){
    for(int i = 0; i < size; ++i){
        if(list[i] == object)
            return i;
    }
    return -1;
}

int main(){
    int arr[5] = {0, 3, 54, 2, 1};
    cout << "find(3, arr, 5) = " << fInd(3, arr, 5) << endl;
    return 0;
}