#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        cout << "Usage: prog_name <filename> <word>";
        return 1;
    }
    ifstream fin(argv[1]);
    if(!fin){
        cout << "Cannot open input file." << endl;
        return 1;
    }
    char word[20]{};
    int counter = 0;
    while(fin >> word){
        if(strcmp(word, argv[2]) == 0)
            ++counter;
    }
    cout << "Your word occurs " << counter << " time(s)" << endl;
    fin.close();
    return 0;
}