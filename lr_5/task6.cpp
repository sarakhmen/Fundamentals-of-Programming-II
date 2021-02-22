#include <iostream>
#include <cstring>
using namespace std;

const size_t NAME_SZ = 50;
const size_t PHONE_NUM = 15;


class Person{
    char name[NAME_SZ];
    char phone[PHONE_NUM];
public:
    Person(char *, char *);
    char *get_name();
    char *get_phone_num();
};

Person::Person(char *name, char *phone){
    if(strlen(name) < NAME_SZ)
        memmove(this->name, name, strlen(name)+1);
    else {
        memmove(this->name, name, NAME_SZ-1);
        this->name[NAME_SZ] = '\0';
    }
    if(strlen(phone) < PHONE_NUM)
        memmove(this->phone, phone, strlen(phone)+1);
    else {
        memmove(this->phone, phone, PHONE_NUM-1);
        this->phone[PHONE_NUM] = '\0';
    }
}

char* Person::get_name(){
    return name;
}

char* Person::get_phone_num(){
    return phone;
}


int main(){
    Person* me = new Person("Artur Sarakhman", "+380971266262");
    cout << "My name: " << me->get_name() << endl;
    cout << "My phone number: " << me->get_phone_num() << endl;
    delete me;
    return 0;
}