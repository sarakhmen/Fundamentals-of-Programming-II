#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: prog_name <filename>";
        return 1;
    }
    ifstream fin(argv[1]);
    if(!fin){
        cout << "Cannot open input file." << endl;
        return 1;
    }
    fin.unsetf(ios::skipws);
    fin.seekg(0, fin.end);
    size_t len = fin.tellg();
    char ch;
    while(len--){
        fin.seekg(len, fin.beg);
        fin >> ch;
        cout << ch;
    }
    fin.close();
    return 0;
}