#include <iostream>
#include <cstdlib>
using namespace std;

long mystrtol(const char *start, char **end, int base = 10){
    long result = strtol(start, end, base);
    return result;
}

int main(){
    char arr[] = "-10023040";
    char *p;
    char **pp = &p;
    long val = mystrtol(arr, pp);
    cout << val << endl;
    return 0;
}