#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct strtype{
    strtype(char const *ptr);
    ~strtype();
    void show();
    friend char* get_string(strtype* strtp);
private:
    char *p;
    int len;
};
char* get_string(strtype* strtp){
    return strtp->p;
}
strtype::strtype(char const *ptr){
    len = strlen(ptr);
    p = (char *)malloc(len + 1);
    if(!p){
        cout << "Allocation error.\n";
        exit(1);
    }
    strcpy(p, ptr);
}
strtype::~strtype(){
    cout << "Freeing p\n";
    free(p);
}
void strtype::show(){
    cout << p << " - length : " << len << '\n';
}
int main(){
    strtype s1("This is a test.");
    char *str = get_string(&s1);
    cout << str;
    return 0;
}
