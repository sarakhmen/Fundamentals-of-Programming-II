#include <iostream>
#include <climits>

using namespace std;

class int_arr_2x3{
    int arr[2][3];
public:
    void set(int x, int y, int val);
    int get(int x, int y);
};

void int_arr_2x3::set(int x, int y, int val){
    if(x < 0 || x > 1){
        cout << "Invalid first argument" << endl;
        return;
    }
     if(y < 0 || x > 2){
        cout << "Invalid second argument" << endl;
        return;
    }
    arr[x][y] = val;
}

int int_arr_2x3::get(int x, int y){
    if(x < 0 || x > 1){
        cout << "Invalid first argument! ";
        return INT_MAX;
    }
     if(y < 0 || x > 2){
        cout << "Invalid second argument! ";
        return INT_MAX;
    }
    return arr[x][y];
}

int main(void){
    int_arr_2x3 a;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 3; ++j)
            a.set(i, j, i*j);
    cout << "Your array:" << endl;
    for(int i = 0; i < 2; ++i){
        for(int j = 0; j < 3; ++j)
            cout << a.get(i, j) << " ";
        cout << endl;
    }
    cout << "a.set(3, 3, 10): "; a.set(3, 3, 10);
    cout << "a.get(2, 5) = " << a.get(2, 5);
    cout << endl;
    return 0;
}