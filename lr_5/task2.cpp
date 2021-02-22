#include <iostream>

using namespace std;

class squares {
    int num, sqr;
public:
    squares(int a, int b) { num = a; sqr = b; }
    void show() { cout << num << ' ' << sqr << "\n"; }
};

int main(){
    const int sz = 10;
    int n = 0;
    squares arr[sz] = {{++n, n*n}, {++n, n*n}, {++n, n*n}, {++n, n*n}, {++n, n*n},
                       {++n, n*n}, {++n, n*n}, {++n, n*n}, {++n, n*n}, {++n, n*n}};
    for(int i = 0; i < sz; ++i)
        arr[i].show();
    return 0;
}
