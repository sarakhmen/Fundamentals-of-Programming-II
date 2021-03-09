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
	list *p;
	sorted sort_ob;
	p = &sort_ob;
	p->store(4);
	p->store(10);
	p->store(1);
	p->store(-4);
	p->store(20);
	for(int i = 0; i < 5; ++i)
		cout << "retrieved: " << p->retrieve() << endl;

	// queue q_ob;
	// stack s_ob;
	// char ch;
	// for(int i=0; i<10; i++) {
	// 	cout << "Stack or Queue? (S/Q):";
	// 	cin >> ch;
	// 	ch = tolower(ch);
	// 	if (ch == 'q')
	// 		p = &q_ob;
	// 	else
	// 		p = &s_ob;
	// 	p->store(i);
	// }
	// cout << "Enter T to terminate\n";
	// for (;;) {
	// 	cout << "Remove from Stack or Queue? (S/Q):";
	// 	cin >> ch;
	// 	ch = tolower(ch);
	// 	if (ch == 't')
	// 		break;
	// 	if (ch == 'q')
	// 		p = &q_ob;
	// 	else
	// 		p = &s_ob;
	// 	cout << p->retrieve() << '\n';
	// }
	// cout << '\n';
	return 0;
}