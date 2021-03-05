#include <iostream>
using namespace std;

#define PRINT(fmtflags, flag) cout << #flag << " = " << bool(fmtflags & flag) << endl

void print_flags(ios::fmtflags flags){
    PRINT(flags, ios::skipws);
    PRINT(flags, ios::left);
    PRINT(flags, ios::right);
    PRINT(flags, ios::internal);
    PRINT(flags, ios::dec);
    PRINT(flags, ios::oct);
    PRINT(flags, ios::hex);
    PRINT(flags, ios::showbase);
    PRINT(flags, ios::showpoint);
    PRINT(flags, ios::showpos);
    PRINT(flags, ios::uppercase);
    PRINT(flags, ios::scientific);
    PRINT(flags, ios::fixed);
    PRINT(flags, ios::unitbuf);
    PRINT(flags, ios::boolalpha);    
} 

int main()
{
    cout.setf(ios::left | ios::showbase | ios::showpoint);
    ios::fmtflags flags = cout.flags();
    print_flags(flags);
    return 0;
}