#include <iostream>
#include <fstream>
#include <cctype>

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
    int frequencies[26]{};
    char ch;
    while((ch = fin.get()) != EOF){
        if(!isalpha(ch))
            continue;
        if(isupper(ch))
            frequencies[ch - 'A']++;
        else    
            frequencies[ch - 'a']++;      
    }
    cout << "Frequency of letters: " << endl;
    for(size_t i = 0; i < 26; ++i)
        cout << char('a' + i) << " appears " << frequencies[i] << " time(s)" << endl;
    fin.close();
    return 0;
}