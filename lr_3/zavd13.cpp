#include <iostream>
using namespace std;
#define SIZE 100

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
		cout << "\nstack is full\n";
		return;
	}
	stck[tos] = ch;
	tos++;
}

char Stack::pop(){
	if(tos == 0){
		cout << "\nstack is empty\n";
		return 0;
	}
	tos--;
	return stck[tos];
}

Stack loadstack(int upper){
    Stack stck;
    stck.init();
    if(26 <= SIZE){
        if(upper)
            for(int i = 0; i < 26; ++i)
                stck.push('A' + i);
        else
            for(int i = 0; i < 26; ++i)
                stck.push('a' + i);
        return stck;
    }
    else{
        cout << "Stack size less than 26" << endl;
        return stck;
    } 
}

int main(){
    Stack stck1 = loadstack(1);
    Stack stck2 = loadstack(0);
    Stack stck3 = stck1;
    char ch;
    cout << "<stck3 = stck1>" << "\nstck1 content: ";
    while(ch = stck1.pop())
        cout << ch << ' ';
    cout << "\nstck2 content: ";
    while(ch = stck2.pop())
        cout << ch << ' ';
    cout << "\nstck3 content: ";
    while(ch = stck3.pop())
        cout << ch << ' ';
    return 0;
}