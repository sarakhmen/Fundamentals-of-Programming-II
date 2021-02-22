#include <iostream>
using namespace std;

int main(){
    double *pd = new double(-123.0987);
    cout << "double variable = " << *pd << endl;
    delete pd;
    return 0;
}