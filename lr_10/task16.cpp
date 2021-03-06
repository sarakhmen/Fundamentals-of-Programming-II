#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: prog_name <filename>";
        return 1;
    }
    fstream fio(argv[1]);
    if(!fio){
        cout << "Cannot open file." << endl;
        return 1;
    }
    fio.unsetf(ios::skipws);
    fio.seekp(0, fio.end);
    size_t len = fio.tellg();
    fio.seekp(0, fio.beg);
    char ch1, ch2;
    for(size_t i = 0; i < len; i+=2){
        ch1 = fio.get();
        ch2 = fio.peek();        
        fio.put(ch1);
        fio.seekp(i, fio.beg);
        fio.put(ch2);
        fio.get();
    }
    fio.seekg(0, fio.beg);
    while(fio){
        ch1 = fio.get();
        cout << ch1;
    }
    cout << endl;
    fio.close();
    return 0;
}