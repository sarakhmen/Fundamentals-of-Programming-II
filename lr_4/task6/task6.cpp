#include <iostream>
#include <fstream>
#include <string>
#include "my_map.h"
#include "my_array.h"
using namespace std;

enum {
    NPREF = 2,
    MAXGEN = 10000
};

void add(Prefix& prefix, const string& s);
void build(Prefix& prefix, ifstream& in);
void generate(int nwords);


string NONWORD = "\n";
my_map statetab;



int main() {
    ifstream in("..\\large_text.txt", ios_base::in);
    if (!in.is_open()) {
        cout << "Error while opening file!" << endl;
        return 1;
    }

    int nwords = MAXGEN;
    Prefix prefix;
    for (int i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    build(prefix, in);
    add(prefix, NONWORD);
    generate(nwords);
    in.close();
    return 0;
}


void add(Prefix& prefix, const string& s) {
    if (prefix.size() == NPREF) {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}


void build(Prefix& prefix, ifstream& in) {
    string buf;
    while (in >> buf) {
        add(prefix, buf);
    }
}


void generate(int nwords) {
    Prefix prefix;
    int i;
    for (i = 0; i < NPREF; i++) {
        add(prefix, NONWORD);
    }
    for (i = 0; i < nwords; i++) {
        Suffix& suf = statetab[prefix];
        const string& w = suf[rand() % suf.size()];
        if (w == NONWORD)
            break;
        cout << w << " ";
        prefix.pop_front();
        prefix.push_back(w);
    }
}
