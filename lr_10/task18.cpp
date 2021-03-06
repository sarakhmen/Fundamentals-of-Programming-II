#include <iostream>
#include <cctype>
using namespace std;

istream &findalpha(istream &stream){
    char ch;
    while(!isalpha(ch = stream.get()));
    return stream.putback(ch);
}

int main(){
    char ch;
    cout << "Enter your string: ";
    cin >> findalpha >> ch;
    cout << "Your alpha: " << ch << endl;
    return 0;
}