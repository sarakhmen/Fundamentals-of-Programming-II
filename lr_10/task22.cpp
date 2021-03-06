#include <iostream>
#include <fstream>

using namespace std;

class Stack {
	fstream stck;
	int tos;
public:
	Stack();
	~Stack(){stck.close();}
    void push(char ch);
	char pop();
};

Stack::Stack(){
    stck.open("stack.txt", ios::in | ios::out | ios::binary);
    if(!stck)
        exit(1);
    tos = -1;
}

void Stack::push(char ch){
	stck << ch;
	tos++;
}

char Stack::pop(){
	if(tos == -1){
		cout << "Stack is empty";
		return 0;
	}
	stck.seekg(tos--, stck.beg);
    return stck.get();
}

int main(){
    Stack stck;
    for(int i = 0; i < 10; ++i){
        cout << "pushing " << char('A' + i) << endl;
        stck.push('A' + i);
    }
    cout << endl;
    for(int i = 0; i < 10; ++i)
        cout << "popping " << stck.pop() << endl;
    return 0;
}