#include <iostream>
#include <strstream>
using namespace std;

int main(){
    char str1[256] = "123.66";
    double val;
    istrstream istr(str1);
    istr >> val;
    cout << "double value = " << val << endl;
    return 0;
}