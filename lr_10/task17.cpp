#include <iostream>
#include <iomanip>
using namespace std;

ostream &my_manip(ostream &stream){
    return stream << "\t\t\t" << setw(20);
}

int main(int argc, char *argv[]){
    cout << left << my_manip << "test string" << endl;
    return 0;
}