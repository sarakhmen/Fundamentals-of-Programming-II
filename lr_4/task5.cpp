#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
using namespace std;

typedef vector<string> Prefix;
unordered_map<Prefix, list<string>> statetab;

enum{
    NPREF = 2,
    NHASH = 5,
    MAXGEN = 10000
};

char NONWORD[] = "\n";

void add(Prefix& prefix, const string& s){
    if(prefix.size() == NPREF){
        statetab[prefix].push_back(s);
        prefix.erase(prefix.begin());
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
        list<string> & suf = statetab[prefix];
        list<string>::iterator it = suf.begin();
        advance(it, rand() % suf.size());
        const string & w = *it;
        if(w == NONWORD) 
            break;
        cout << w << " ";
        prefix.erase(prefix.begin());
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
    return 0;
}