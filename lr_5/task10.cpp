#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;


struct node{
    char *data;
    node *next;

    node(const char*);
    ~node();
};

class simple_list{
    size_t size;
    node *bgn;
public:
    simple_list() : bgn(nullptr), size(0){}
    ~simple_list();
    size_t get_size() {return size;}
    node *push_front(const char*);
    node *insert(const char *, const char *, bool);
    bool erase(const char *);
    node *begin() {return bgn;}
    void merge(simple_list&);
    node *find(const char*);
    bool split(simple_list&, const char*);

};


node::node(const char *str){
    data = new char[strlen(str)+1];
    if(!data){
        cout << "Allocation error.";
        exit(1);
    }
    strcpy(data, str);
    next = nullptr;
}

node::~node(){
    cout << " with data: " << data << endl;
    delete[] data;
}


simple_list::~simple_list(){
    node *prev,
         *curr;
    for(curr = bgn; curr != nullptr;){
        prev = curr;
        curr = curr->next;
        cout << "Deleting node";
        delete prev;
    }
}

node *simple_list::push_front(const char *str){
    node *temp = new node(str);
    if(!temp){
        cout << "Allocation error.";
        exit(1);
    }
    temp->next = bgn;
    bgn = temp;
    size++;
    return temp;
}

bool simple_list::erase(const char *str){
    if(size == 0){
        cout << "The list is empty!" << endl;
        return false;
    }
    for(node **temp = &bgn; *temp != nullptr; temp = &(*temp)->next){
        if(strcmp((*temp)->data, str) == 0){
            node *p = (*temp)->next;
            cout << "Deleting node";
            delete (*temp);
            (*temp) = p;
            size--;
            return true;
        }
    }
    cout << "Given element doesn't exist!" << endl;
    return false;
}

node *simple_list::insert(const char *member, const char *new_item, bool before){
    if(size == 0){
        cout << "The list is empty!" << endl;
        return nullptr;
    }
    for(node **temp = &bgn; *temp != nullptr; temp = &(*temp)->next){
        if(strcmp((*temp)->data, member) == 0){

            if(before){
                node *p = *temp;
                *temp = new node(new_item);
                (*temp)->next = p;
                size++;
                return *temp;
            }
            else{
                temp = &(*temp)->next;
                node *p = *temp;
                *temp = new node(new_item);
                (*temp)->next = p;
                size++;
                return *temp;
            }
        }
    }   
    cout << "There isn't such a member" << endl; 
    return nullptr;
}

void simple_list::merge(simple_list& ls){
    node **temp;
    for(temp = &bgn; *temp != nullptr; temp = &(*temp)->next);
    *temp = ls.bgn;
    size += ls.get_size();
    ls.size = 0;
    ls.bgn = nullptr;
}

node *simple_list::find(const char *str){
    for(node *temp = bgn; temp!=nullptr; temp=temp->next){
        if(strcmp(temp->data, str)==0)
            return temp; 
    }
    cout << "Nothing found!" << endl;
    return nullptr;
}

bool simple_list::split(simple_list& ls, const char *str){
    node **temp;
    for(temp = &bgn; *temp != nullptr; temp = &(*temp)->next){
        if(strcmp((*temp)->data, str) == 0){
            ls.~simple_list();
            ls.bgn = *temp;
            *temp = nullptr;
            size_t sz = 0;
            for(node *p = ls.bgn; p!=nullptr; p = p->next)
                sz++;
            size -= sz;
            ls.size = sz;       
            return true;
        }
    }
    return false;
}


void copy(node *dest, node *source){
    delete[] dest->data;
    dest->data = new char[strlen(source->data)+1];
    strcpy(dest->data, source->data);
    dest->next = nullptr;
}


int main(){
    simple_list sml;
    cout << "adding some elements..." << endl;
    sml.push_front("first");
    sml.insert("first", "inserted after", false);
    sml.insert("first", "inserted before", true);
    sml.erase("first");
    node *copied = new node("copied node");
    copy(copied, sml.find("inserted before"));
    cout << "copied data = " << copied->data << endl;
    sml.push_front("something1");
    sml.push_front("something2");
    simple_list sml2;
    sml.split(sml2, "something1");
    node *tmp;
    cout << "first part of the list: ";
    for(tmp = sml.begin(); tmp!=nullptr; tmp=tmp->next)
        cout << tmp->data << "   ";
    cout << endl;
    cout << "second part of the list: ";
    for(tmp = sml2.begin(); tmp!=nullptr; tmp=tmp->next)
        cout << tmp->data << "   ";
    cout << endl;
    sml.merge(sml2);
    cout << "merged list: ";
    for(tmp = sml.begin(); tmp!=nullptr; tmp=tmp->next)
        cout << tmp->data << "   ";
    cout << endl;
    return 0;
}