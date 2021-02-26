#include <iostream>
#include <cstring>
using namespace std;

char *reverse(char *str, int count = -1){
    int len = strlen(str);
    if(count == -1 || count > len)
        count = len;
    int temp;
    for(int i = 0; i < count/2; ++i){
        temp = str[i];
        str[i] = str[count-1-i];
        str[count-1-i] = temp;
    }
    return str;
}


int main(){
    char arr[] = "cucumber";
    reverse(arr, 4);
    cout << arr << endl;
    return 0;
}