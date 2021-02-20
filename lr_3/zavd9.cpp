#include <iostream>
using namespace std;

class who{
    char name;
public:
    who(char ch);
    ~who();
};

who::who(char ch){
    cout << "Constructing who #" << ch << endl;
    name = ch;
}

who::~who(){
    cout << "destroying who #" << name << endl;
}

who make_who(){
    static char ch = 'A';
    who who_obj(ch);
    ++ch;
    return who_obj;
}

int main(){
    who wh('G');
    wh = make_who();
    return 0;
}