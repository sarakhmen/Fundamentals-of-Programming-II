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
    char temp[100];
    size_t count = 0;
    while(!fin.eof()){
        fin.get(temp, 99, ' ');
        fin.get();
        cout << "finded " << temp << count << endl;
        ++count;
    }
    cout << "Your file consists of " << count << " word(s)" << endl;
    fin.close();
    return 0;
}