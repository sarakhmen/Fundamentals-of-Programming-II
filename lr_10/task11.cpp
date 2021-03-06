#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class account {
    int custom;
    char name[80];
    double balance;
public:
    account(int c, const char *n, double b) {
        custom = c;
        strcpy(name, n);
        balance = b;
    }
    friend ostream &operator <<(ostream &stream, account &obj){
        return stream << obj.custom << ' ' << obj.name << ' ' << obj.balance << endl;    }
};

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: prog_name <filename>";
        return 1;
    }
    ofstream fout(argv[1]);
    if(!fout){
        cout << "Cannot open output file." << endl;
        return 1;
    }
    account ac(10, "smthng smthng", 2000);
    fout << ac;
    fout.close();
    return 0;
}