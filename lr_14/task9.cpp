#include <iostream>
#include <strstream>
using namespace std;

int main(){
    char str1[256] = "test string";
    char str2[256];
    ostrstream ostr(str2, 256);
    ostr << str1 << '\0';
    cout << str2;    
    return 0;
}