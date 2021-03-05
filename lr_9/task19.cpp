#include <iostream>
using namespace std;
#define SIZE 100


class stack {
    char stck[SIZE]; // holds the stack
    int tos; // index of top -of - stack
public:
    stack();
    void push(char ch); // push character on stack
    char pop(); // pop character from stack
    friend ostream &operator <<(ostream &stream, stack &st);
};

// Initialize the stack:
stack::stack() {
    tos = 0;   
}

// Push a character
void stack::push (char ch) {
    if (tos == SIZE) {
        cout << "Stack is full\n";
        return ;
    }
    stck[tos] = ch;

    tos++;
}
// Pop a character:
char stack::pop() {
    if (tos==0) {
        cout << "Stack is empty\n";
        return 0;
    }
    tos--;
    return stck[tos];
}

ostream &operator <<(ostream &stream, stack &st){
    for(int i = st.tos - 1; i >= 0; --i)
        stream << st.stck[i] << " ";
    cout << endl;
    return stream;
}


int main(){
    stack st;
    for(int i = 0; i < 10; ++i)
        st.push('A' + i);
    cout << "stack content: " << st;
    return 0;
}