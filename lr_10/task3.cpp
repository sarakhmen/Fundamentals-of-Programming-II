#include <iostream>
using namespace std;

class date {
    char d[9]; // store date as string : mm/dd/yy
public:
    friend ostream &operator <<(ostream &stream, date &obj){
        return stream << obj.d;
    }
    friend istream & operator >>(istream &stream, date &obj){
        cout << "Enter date in format: mm/dd/yy" << endl;
        return stream >> obj.d;
    }
};


int main(){
    date d;
    cin >> d;
    cout << "Your date: ";
    cout << d;
    return 0;
}