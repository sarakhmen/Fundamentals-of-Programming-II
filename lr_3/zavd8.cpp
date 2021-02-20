#include <iostream>
using namespace std;
#define SIZE 10

class Stack {
	char stck[SIZE];
	int tos;
public:
	Stack();
	void push(char ch);
	char pop();
};

Stack::Stack(){
    tos = 0;
}

void Stack::push(char ch){
	if(tos == SIZE)
		return;
	stck[tos] = ch;
	tos++;
}

char Stack::pop(){
	if(tos == 0)
		return 0;
	tos--;
	return stck[tos];
}

void showstack(Stack s){
    char ch;
    cout << "stack content: ";
    while((ch = s.pop()) != 0)
        cout << ch; 
    cout << endl;
}

int main(){
	Stack s1, s2;
    s1.push('a');
	s2.push('x');
	s1.push('b');
	s2.push('y');
	s1.push('c');
    s2.push('z');
	showstack(s1);
    showstack(s2);
    return 0;
}