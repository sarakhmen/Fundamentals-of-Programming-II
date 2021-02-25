#include <iostream>
#include <cstring>
using namespace std;

class strtype {
    char *p;
    int len;
public:
    strtype();
    strtype(const char *, int);
    ~strtype();
    char *getstring() { return p; }
    int getlength() { return len; }
    char &put(int i);
    char get(int i);
};

strtype::~strtype(){
    delete[] p;
}

strtype::strtype(){
    p = new char[255];
    if(!p) exit(1);
    len = 255;
    *p = '\n';
}

strtype::strtype(const char* str, int length){
    p = new char[length];
    if(!p) exit(1);
    if(strlen(str)+1 <= length)
        strcpy(p, str);
    else{
        strncpy(p, str, length-1);
        p[length] = '\n';
    }
    len = length;
}

char &strtype::put(int i){
    if(i<0 || i >= len){
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[i];
}

char strtype::get(int i){
    if(i<0 || i >= len){
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[i];
}


int main(){
    strtype str1, str2("test string", 20);
    strcpy(str1.getstring(), "another test string");
    cout << str2.getstring() << endl;
    cout << str1.getstring() << endl;
    return 0;
}