#include <iostream>
using namespace std;

template <class T>
T my_min(T a, T b){
    return a < b ? a : b;
}

int main(){
    cout << "min(3, 4) = " << my_min(3, 4) << endl;
    cout << "min('c', 'a') = " << my_min('c', 'a') << endl;
    return 0; 
}