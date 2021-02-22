#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <deque>
using namespace std;

typedef deque<string> Prefix;
map<Prefix, vector<string>> statetab;

enum{
    NPREF = 2,
    NHASH = 5,
    MAXGEN = 10000
};

char NONWORD[] = "\n";

void add(Prefix& prefix, const string& s){
    if(prefix.size() == NPREF){
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

void build(Prefix & prefix, ifstream & in){
    string buf;
    while(in >> buf){
         add(prefix, buf);
    }
}

void generate(int nwords){
    Prefix prefix;
    int i;
    for(i = 0; i < NPREF; i++){
        add(prefix, NONWORD);
    }
    for(i = 0; i < nwords; i++){
        vector<string> & suf = statetab[prefix];
        const string & w = suf[rand() % suf.size()];
        if(w == NONWORD) 
            break;
        cout << w << " ";
        prefix.pop_front();
        prefix.push_back(w);
    }
}

int main(){
    ifstream in("brooks.txt", ios_base::in);
    if (!in.is_open()) {
		cout << "Error while opening file!" << endl;
		return 1;
	}
    int nwords = MAXGEN;
    Prefix prefix;
    for(int i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    build(prefix, in);
    add(prefix, NONWORD);
    generate(nwords);
    in.close();
    return 0;
}