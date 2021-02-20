#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;
class Dice;
void roll_n_times(Dice&, int);

class Dice{
    char name[10];
    int val;
public:
    Dice(const char* n);
    void roll();
    int get_value();
};

Dice::Dice(const char* n){
    int len = strlen(n);
    if(!len){
        cout << "Error: invalid name!" << endl;
        exit(1);
    }
    strcpy(name, n);
    name[9] = '\0';
}

void Dice::roll(){
    val = rand()%6 + 1;
    cout << "Dice " << name << " rolled value = " << val << endl;
}

int Dice::get_value(){
    return val;
}

void roll_n_times(Dice& d, int n){
    for(int i = 0; i < n; ++i)
        d.roll();
}

int main(){
    Dice d1("AAA"), 
         d2("BBB"), 
         d3("CCC"),
         d4("EEE");
    srand((unsigned)time(NULL));
    roll_n_times(d1, 5);
    roll_n_times(d2, 5);
    roll_n_times(d3, 5);
    roll_n_times(d4, 5);    
    return 0;
}