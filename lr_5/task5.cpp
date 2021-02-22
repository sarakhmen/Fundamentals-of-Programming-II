#include <iostream>
using namespace std;

int main(){
    long *pl = new long(13);
    float *pf = new float(23.9);
    char *pc = new char('J');
    cout << *pl << ' ' << *pf << ' ' << *pc << endl;
    delete pl;
    delete pf;
    delete pc;
    return 0;
}