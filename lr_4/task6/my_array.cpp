#include "my_array.h"
#include <iostream>


my_array::my_array() {
    sz = 1;
    pos = 0;
    multilpier = 2;
    arr = new string[sz];
    if (!arr) {
        cout << "Memory allocation error!" << endl;
        exit(1);
    }
}


my_array::~my_array() {
    delete[] arr;
}


void my_array::pop_front() {
    if (pos == 0)
        return;
    --pos;
    for (size_t i = 0; i < pos; ++i) {
        arr[i] = arr[i + 1];
    }
}


void my_array::push_back(const string& s) {
    if (pos == sz) {
        sz *= multilpier;
        string* temp = new string[sz];
        if (!temp) {
            cout << "Memory allocation error!" << endl;
            exit(1);
        }
        for (size_t i = 0; i < pos; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[pos++] = s;
}


size_t my_array::size() const {
    return pos;
}


string& my_array::operator[](size_t index) {
    if (index >= pos) {
        cout << "Array index out of bound!" << endl;
        exit(1);
    }
    return arr[index];
}


bool my_array::operator==(my_array& cont) {
    if (this->sz != cont.size())
        return false;
    for (size_t i = 0; i < this->sz; ++i) {
        if (this->arr[i] != cont[i])
            return false;
    }
    return true;
}


my_array& my_array::operator=(my_array& cont) {
    size_t sz = 2,
           new_pos = cont.size();
    for (; sz < new_pos; sz *= 2);
    string* temp = new string[sz];
    if (!temp) {
        cout << "Allocation error!" << endl;
        exit(1);
    }
    for (size_t i = 0; i < new_pos; ++i) {
        temp[i] = cont[i];
    }
    delete[] this->arr;
    this->arr = temp;
    this->pos = new_pos;
    this->sz = sz;
    this->multilpier = cont.multilpier;
    return *this;
}