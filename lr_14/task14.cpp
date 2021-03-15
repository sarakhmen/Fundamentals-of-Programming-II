#include <iostream>
using namespace std;

namespace my_containers{
        
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

    class array{
        int *p;
        int size;
    public:
        array(int sz) {
            p = new int[sz];
            if(!p) exit(1);
            size = sz;
            cout << "Using 'normal' constructor.\n";
        }
        ~array() { delete [] p; }
        array(const array &a);
        void put(int i, int j){
            if(i>=0 && i<size)
                p[i] = j;
        }
        int get(int i) const { return p[i];}
    };

    array::array(const array &obj){
        size = obj.size;
        p = new int[obj.size];
        if(!p) exit(1);
        for(int i = 0; i < obj.size; i++)
            p[i] = obj.p[i];
        cout << "using copy constructor.\n";
    }

}



int main(){
    return 0;
}