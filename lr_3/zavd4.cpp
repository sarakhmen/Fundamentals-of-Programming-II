#include <iostream>
using namespace std;

inline int fact(int n){
    if(n <= 1)
        return 1;
    return fact(n-1);
}

inline int sum(int n){
    int s = 0;
    for(int i = 1; i <= n ; ++i){
        s += i;
    }
    return s;
}

inline int counter(){
    static int c = -1;
    return ++c;
}

inline double dmax(double a, double b){
    if (a>b)
        return a;
    else 
        return b;
} 

inline void switch_(int a){
    switch(a){
    case 1:
        cout << a;
    default:
        cout << "something else";
    }
}

inline int goto_(int a){
    label1:
    a += 1000;
    if(a < 1000)
        goto label1;
    return a;
}

int main(){
    int a = 5, b = 10;
    int c;
    a = fact(a);
    b = sum(b);
    c = counter();
    a = dmax(a, b);
    switch(c);
    b = goto_(b);
    cout << a << " " << b << endl;
    return 0;
}