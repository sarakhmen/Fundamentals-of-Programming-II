#include <iostream>
#include <cstring>
using namespace std;

const int SCREEN = 80;

void center(char *s){
    int len = strlen(s);
    int gap = (SCREEN - len) / 2;
    cout.width(len+gap);
    cout << s << endl;
}

int main(){
    char arr[] = "string to be centrised";
    center(arr);
    cout << "something else" << endl;
    return 0;
}