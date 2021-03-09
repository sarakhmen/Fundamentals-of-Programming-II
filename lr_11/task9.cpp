#include <iostream>
using namespace std;

class list {
public:
	list *head;
	list *tail;
	list *next;
	int num;
	list() {head = tail = next = NULL;}
	virtual void store(int i) = 0;
	virtual int retrieve() = 0;
	virtual ~list();
};

list::~list() {
	list *temp;
	for(temp = head; temp!=NULL; temp = head) {
		head = head->next;
		delete temp;
	}
}

class queue: public list {
public:
	void store(int i);
	int retrieve();
};

void queue::store(int i) {
	list *item;
	item = new queue;
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

int queue::retrieve() {
	int i;
	list *p;
	if(!head) {
		cout << "List empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

class stack: public list {
public:
	void store(int i);
	int retrieve();
};

void stack::store(int i) {
	list *item;
	item = new stack;
	if(!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if(head) item->next = head;
	head = item;
	if(!tail) tail = head;
}

int stack::retrieve() {
	int i;
	list *p;
	if(!head) {
		cout << "List empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

class sorted: public list {
public:
	void store(int i);
	int retrieve();
    list &operator +(int i){
        store(i);
        return *this;
        }
    int operator -(){
        return retrieve();
    }
};

void sorted::store(int i) {
	list *item;
	list *p;
	item = new sorted;
	if(!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if(!head)
		head = tail = item;
	else if(head->num >= item->num){
		item->next = head;
		head = item;
	}
	else if(tail->num <= item->num){
		tail->next = item;
		tail = item;
	}
	else{
		p = head;
		while(true){
			if(p->next->num >= item->num){
				item->next = p->next;
				p->next = item;
				break;
			}
			p = p->next;
		}
	}
}

int sorted::retrieve() {
	int i;
	list *p;
	if(!head) {
		cout << "List empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	if(!head)
		tail = NULL;
	delete p;
	return i;
}

int main() {
	sorted sort_ob;
	sort_ob + 4;
    sort_ob + 2;
    sort_ob + 10;
    sort_ob + -4;
    sort_ob + 1;
    for(int i = 0; i < 5; ++i)
		cout << "retrieved: " << -sort_ob << endl;
	return 0;
}