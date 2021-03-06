#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Usage: prog_name <filename1> <filename2>";
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if(!fin){
        cout << "Cannot open input file." << endl;
        return 1;
    }
    if(!fout){
        cout << "Cannot open output file." << endl;
        return 1;
    }
    char ch;
    size_t amount = 0;
    while((ch = fin.get()) != EOF){
        ++amount;
        fout << ch;
    }
    cout << "characters copied: " << amount << endl;
    fin.close();
    fout.close();
    return 0;
}