#include <iostream>
#include <Windows.h>

using namespace std;

void myclreol(SHORT shift = -1){  
    HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console_handler, &csbi);
    COORD coord;
    if((shift < 0) || (shift > csbi.dwCursorPosition.X))
        shift = csbi.dwCursorPosition.X;
    coord.X = csbi.dwCursorPosition.X - shift;
    coord.Y = csbi.dwCursorPosition.Y;
    FillConsoleOutputCharacter(console_handler, ' ', shift, coord, &count);
    SetConsoleCursorPosition(console_handler, coord);
}

int main(){
    cout << "test string";
    myclreol();
    cout << "another test string";
    myclreol(10);
    cout << "<<end of test>>";
    return 0;
}