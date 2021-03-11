#include <iostream>
#include <map>

using namespace std;

template <class T>
T find_most(T *arr, int size){
    T value;
    int count;
    map<T, int> mp;
    for(int i = 0; i < size; ++i){
        mp[arr[i]]++;
    }
    value = mp.begin()->first;
    count = mp.begin()->second;
    for(auto it = ++mp.begin(); it != mp.end(); ++it){
        if(it->second > count){
            count = it->second;
            value = it->first;
        }
    }
    return value;
}

int main(){
    int arr[10] = {1, 2, 3, 1, 2, 5, 6, 7, 7, 7};
    cout << "the most frequent value = " << find_most(arr, 10);
    return 0;
}