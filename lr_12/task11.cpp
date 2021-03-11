#include <iostream>
#include <exception>
using namespace std;

void my_terminate(){
    cout << "The exeption wasn't handled, terminating the program!" << endl;
    abort();    
}

int main(){
    set_terminate(my_terminate);
    try{
        throw 0;
    }
    catch(char &ch){
        cout << "char caught!" << endl;
    }
    return 0;
}