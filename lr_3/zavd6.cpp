#include <iostream>
using namespace std;
#define SIZE 10

class Stack {
	char stck[SIZE];
	int tos;
public:
	void init();
	void push(char ch);
	char pop();
};

inline void Stack::init(){ tos = 0; }

void Stack::push(char ch){
	if(tos == SIZE){
		cout << "stack is full";
		return;
	}
	stck[tos] = ch;
	tos++;
}

char Stack::pop(){
	if(tos == 0){
		cout << "Stack is empty";
		return 0;
	}
	tos--;
	return stck[tos];
}


int main(){
	Stack s1, s2;
	s1.init();
    s2.init();
    s1.push('a');
	s2.push('x');
	s1.push('b');
	s2.push('y');
	s1.push('c');
    s2.push('z');
	for(int i = 0; i<3; ++i) cout << "Pop s1: " << s1.pop() << '\n';
	for(int i = 0; i<3; ++i) cout << "Pop s2: " << s2.pop() << '\n';
    return 0;
}