#include <iostream>

using namespace std;

template <class T>
class Input{
    T val;
public:
    Input(const char *str, T min, T max){
        do{
            cout << str;
            cin >> val;
        } while(val < min || val > max);
    }
    T get_val(){ return val;}
};


int main(){
    cout << "start" << endl;
    Input<int> in("Enter number in range 1:10: ", 1, 10);
    cout << "end" << endl;
    return 0;
}


