#include <iostream>
#include <fstream>

using namespace std;

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
    char str[100];
    cout << "Enter data to save, '$' to stop" << endl;
    while(true){
        cin.getline(str, 99);
        if(*str == '$')
            break;
        fout << str << endl;
    }
    fout.close();
    return 0;
}