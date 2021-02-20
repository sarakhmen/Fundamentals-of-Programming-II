#include <iostream>
using namespace std;

class my_class{
public:
    const char *name;
    my_class(const char* str):name(str){}
};

my_class create_my_class(){
    char name[] = "test";
    my_class obj(name);
    return obj;
}

int main(){
    my_class mcl = create_my_class(); 
    cout << "Object name = " << mcl.name << endl;
    return 0;
}