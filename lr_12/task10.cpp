#include <iostream>
#include <exception>
using namespace std;

template <class Type1, class Type2>
class List {
public:
	struct Pair {
		Type1 first{};
		Type2 second{};
	};
	Pair m_pair;
	List<Type1, Type2>* head;
	List<Type1, Type2>* tail;
	List<Type1, Type2>* next;
	List() { head = tail = next = NULL; }
	virtual void store(Type1 val1, Type2 val2) = 0;
	virtual Pair retrieve() = 0;
	virtual ~List();
};

template <class Type1, class Type2>
List<Type1, Type2>::~List() {
	List<Type1, Type2>* temp;
	for (temp = head; temp != NULL; temp = head) {
		head = head->next;
		delete temp;
	}
}

template <class Type1, class Type2>
class Stack : public List<Type1, Type2> {
	using List<Type1, Type2>::head;
	using List<Type1, Type2>::tail;
public:
	void store(Type1 val1, Type2 val2);
	typename Stack<Type1, Type2>::Pair retrieve();
};

template <class Type1, class Type2>
void Stack<Type1, Type2>::store(Type1 val1, Type2 val2) {
	List<Type1, Type2>* item;
    try {
	    item = new Stack<Type1, Type2>;
    } catch(const bad_alloc &e){
        e.what();
        throw;
    }
    
    item->m_pair.first = val1;
	item->m_pair.second = val2;
	if (head) item->next = head;
	head = item;
	if (!tail) tail = head;
}

template <class Type1, class Type2>
typename Stack<Type1, Type2>::Pair Stack<Type1, Type2>::retrieve() {
    typename Stack<Type1, Type2>::Pair pr;
    List<Type1, Type2>* p;
    try{
        if(!head)
            throw "stack is empty!";
    }
    catch(const char *str){
        cout << str << endl;
        throw;
    }
    pr.first = head->m_pair.first;
    pr.second = head->m_pair.second;
    p = head;
    head = head->next;
    delete p;
    return pr;

}


int main() {
	Stack<int, double> s;
    try{
        for(int i = 0; i < 20; ++i)
            s.store(i, i+0.5);
        cout << "Our retrieved pairs: " << endl;
        for(int i = 0; i < 21; ++i){
            auto pr = s.retrieve();
            cout << pr.first << ' ' << pr.second << endl;
        }
    } catch(...){
        cout << "Error occurs!" << endl;
    }
    return 0;
}