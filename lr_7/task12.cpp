#include <iostream>
#include <cstring>

using namespace std;

class strtype{
    int len;
    char *p;
public:
    strtype(char const *s);
    ~strtype(){delete [] p;}
    char &operator[] (int i);
};

strtype::strtype(char const *s){
    len = strlen(s + 1);
    p = new char[len];
    if(!p){
        cout << "allocation error!";
        exit(1);
    }
    strcpy(p, s);
}

char &strtype::operator[](int i){
    if(i < 0 || i >= len){
        cout << "Bounds error!";
        exit(1);
    }
    return p[i];
}


int main(void){
    strtype str("something");
    cout << str[0] << endl;
    str[0] = 'S';
    cout << str[0] << endl;
    return 0;
}