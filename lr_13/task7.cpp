#include <iostream>
using namespace std;

class DataStruct {
public:
	DataStruct *head;
	DataStruct *tail;
	DataStruct *next;
	int num;
	DataStruct() {head = tail = next = NULL;}
	virtual void store(int i) = 0;
	virtual int retrieve() = 0;
	virtual ~DataStruct();
};

DataStruct::~DataStruct() {
	DataStruct *temp;
	for(temp = head; temp!=NULL; temp = head) {
		head = head->next;
		delete temp;
	}
}

class Queue: public DataStruct {
public:
	void store(int i);
	int retrieve();
};

void Queue::store(int i) {
	DataStruct *item;
	item = new Queue;
	if(!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if(tail) tail->next = item;
	tail = item;
	item->next = NULL;
	if(!head) head = tail;
}

int Queue::retrieve() {
	int i;
	DataStruct *p;
	if(!head) {
		cout << "DataStruct empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

class Stack: public DataStruct {
public:
	void store(int i);
	int retrieve();
};

void Stack::store(int i) {
	DataStruct *item;
	item = new Stack;
	if(!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if(head) item->next = head;
	head = item;
	if(!tail) tail = head;
}

int Stack::retrieve() {
	int i;
	DataStruct *p;
	if(!head) {
		cout << "DataStruct empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}


DataStruct *DataStructFactory(char what){
    if(what == 's')
        return new(nothrow) Stack;
    else if(what == 'q')
        return new(nothrow) Queue;
    else 
        return NULL;
}


int main(){
    DataStruct *p = DataStructFactory('q');
    for(int i = 0; i < 10; ++i)
        p->store(i);
    cout << "retrieve queue: ";
    for(int i = 0; i < 10; ++i)
        cout << p->retrieve() << ' ';  
    cout << endl;
    p = DataStructFactory('s');
    for(int i = 0; i < 10; ++i)
        p->store(i);
    cout << "retrieve stack: ";
    for(int i = 0; i < 10; ++i)
        cout << p->retrieve() << ' ';  
    return 0;
}