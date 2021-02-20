#include <iostream>
using namespace std;

class pr1;
class pr2;
bool inuse(pr1, pr2, int);

class pr1{
    int printing;
public:
    pr1(){ printing = 0; }
    void set_print(int status) { printing  = status; }
    friend bool inuse(pr1, pr2, int);
};

class pr2{
    int printing;
public:
    pr2(){ printing = 0; }
    void set_print(int status) { printing  = status; }
    friend bool inuse(pr1, pr2, int);
};

bool inuse(pr1 obj1, pr2 obj2, int status){
    if(obj1.printing == status || obj2.printing == status)
        return true;
    return false;
}

int main(){
    pr1 obj1;
    pr2 obj2;
    obj1.set_print(10);
    obj2.set_print(5);
    cout << "Printer #10 " << (inuse(obj1, obj2, 10) ? "is" : "isn't") << " inuse\n";
    cout << "Printer #1 " << (inuse(obj1, obj2, 1) ? "is" : "isn't") << " inuse\n";
    return 0;
}

