#include <iostream>

using namespace std;

int main(){
    char my_very_large_char_array[2][2][2][2][2][2][2][2];
    char& ch = my_very_large_char_array[0][0][0][0][0][0][0][0];
    ch = 'A';
    if(ch == 'A')  
        ch = 'A' + 1;
    /* no need to use 
    if(my_very_large_char_array[0][0][0][0][0][0][0][0] == 'A')
        my_very_large_char_array[0][0][0][0][0][0][0][0] = 'A' + 1; 
    */
    cout << ch << endl;
    return 0;
}