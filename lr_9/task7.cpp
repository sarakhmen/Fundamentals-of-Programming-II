#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

const int SCREEN = 80;

void center(char *s){
    int len = strlen(s);
    int gap = (SCREEN - len) / 2;
    cout << setw(len+gap) << s << endl;
}

int main(){
    cout << setprecision(5) << right << fixed;
    cout << setw(10) << 'x' << setw(10) << "log(x)" 
        << setw(10) << "log10(x)" << endl;
    for(int i = 2; i < 101; ++i){
    cout << setw(10) << i << setw(10) << log(i) 
        << setw(10) << log10(i) << endl;
    }
    cout << endl;
    char arr[] = "string to be centrised";
    center(arr);
    return 0;
}