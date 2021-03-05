#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    cout << 100 << endl;
    cout << hex << 100 << endl;
    cout << oct << 100 << endl;
    cout << setw(20) << setprecision(2) << setfill('*') 
         << fixed << left << 1000.5364 << endl;
    return 0;
}