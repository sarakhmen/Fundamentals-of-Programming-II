#include <iostream>
using namespace std;

class Stack {
	char *stck;
	int size;
	int tos;
public:
	Stack(int size);
	void push(char ch);
	char pop();
};

Stack::Stack(int size){
	stck = (char *)malloc(size);
	if(!stck){
		cout << "Allocation error.\n";
		exit(1);
	}
	this->size = size;
	tos = 0;
}

void Stack::push(char ch){
	if(tos == size){
		cout << "stack is full" << endl;
		return;
	}
	stck[tos] = ch;
	tos++;
}


char Stack::pop(){
	if(tos == 0){
		cout << "Stack is empty" << endl;
		return 0;
	}
	tos--;
	return stck[tos];
}


int main(){
	Stack s(4);
	s.push('a');
	s.push('b');
	s.push('c');
	s.push('d');
	s.push('f');
	for(int i = 0; i<5; ++i)
		cout << "Pop s: " << s.pop() << endl;
	return 0;
}