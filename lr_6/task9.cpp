#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;

class Date{
    int day, month, year;
public:
    Date(int m, int d, int y){
        day = d;
        month = m;
        year = y;
    }
    Date(time_t m, time_t d, time_t y){
        day = d;
        month = m;
        year = y;
    }
    Date(char const *str){
        sscanf(str, "%d%*c%d%*c%d", &month, &day, &year);
    }
    void show(){
        cout << month << '/' << day << '/' << year << '\n';
    }
};


int main(){
    Date strdate("19/03/19");
    strdate.show();

    Date intdate(19, 03, 19);
    intdate.show();

    Date timedate((time_t)19, (time_t)03, (time_t)19);
    timedate.show();
    return 0;
}