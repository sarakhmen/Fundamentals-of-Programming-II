#include <iostream>
#include <iomanip>
using namespace std;

ostream &my_manip(ostream &stream){
    return stream << scientific << uppercase;
}

int main(){
    cout << my_manip << 1234. << endl;
    return 0;
}