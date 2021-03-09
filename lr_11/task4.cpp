#include <iostream>
#include <fstream>
using namespace std;

ostream &set_out_pos_81(ostream &stream){
    return stream.seekp(81, stream.beg);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: prog_name <filename>";
        return 1;
    }
    ofstream out(argv[1]);
    if(!out){
        cout << "Cannot open output file." << endl;
        return 1;
    }
    out << set_out_pos_81 << "something" << endl;
    out.close();
    return 0;
}