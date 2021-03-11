#include <iostream>
using namespace std;

template <class T>
class List {
public:
	List<T>* head;
	List<T>* tail;
	List<T>* next;
	T num;
	List() { head = tail = next = NULL; num = 0; }
	virtual void store(T i) = 0;
	virtual T retrieve() = 0;
	virtual ~List();
};

template <class T>
List<T>::~List() {
	List<T>* temp;
	for (temp = head; temp != NULL; temp = head) {
		head = head->next;
		delete temp;
	}
}

template <class T>
class Queue : public List<T> {
	using List<T>::num;
	using List<T>::head;
	using List<T>::tail;
public:
	void store(T i);
	T retrieve();
};

template <class T>
void Queue<T>::store(T i) {
	List<T>* item;
	item = new Queue<T>;
	if (!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if (tail) tail->next = item;
	tail = item;
	item->next = NULL;
	if (!head) head = tail;
}

template <class T>
T Queue<T>::retrieve() {
	T i;
	List<T>* p;
	if (!head) {
		cout << "List empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

template <class T>
class Stack : public List<T> {
	using List<T>::num;
	using List<T>::head;
	using List<T>::tail;
public:
	void store(T i);
	T retrieve();
};

template <class T>
void Stack<T>::store(T i) {
	List<T>* item;
	item = new Stack<T>;
	if (!item) {
		cout << "Allocation error.\n";
		exit(1);
	}
	item->num = i;
	if (head) item->next = head;
	head = item;
	if (!tail) tail = head;
}

template <class T>
T Stack<T>::retrieve() {
	T i;
	List<T>* p;
	if (!head) {
		cout << "List empty.\n";
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}


int main() {
	Queue<int> qi;
	qi.store(10);
    qi.store(20);
	cout << qi.retrieve() << ' ' << qi.retrieve() << endl;
    Queue<double> qd;
    qd.store(0.5);
    qd.store(1.5);
    cout << qd.retrieve() << ' ' << qd.retrieve() << endl;
    Stack<char> sch;
    sch.store('A');
    sch.store('B');
    cout << sch.retrieve() << ' ' << sch.retrieve() << endl;
	return 0;
}