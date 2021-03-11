#include <iostream>

using namespace std;

double divide (double a, double b) {
    try{
        if(b == 0)
            throw 0;
    }
    catch(int){
        cout << "Division by zero!" << endl;
        exit(1);
    }
    return a/b;
}

int main(){
    cout << "start" << endl;
    cout << divide(10, 2) << '\n' << divide(5, 0) << endl;
    cout << "end" << endl;
    return 0;
}