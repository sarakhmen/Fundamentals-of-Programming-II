#include "my_map.h"


my_map::pair::~pair() {
    if (next)
        delete next;
}


my_map::my_map(){
    multiplier = 31;
    sz = 2000;
    hashtab = new pair * [sz] {};
    
}


my_map::~my_map() {
    for (size_t i = 0; i < sz; ++i) {
        if (hashtab[i] != 0)
            delete hashtab[i];
    }
    delete[] hashtab;
}


size_t my_map::hash(Prefix& mc) {
    size_t h = 0;
    unsigned char* p;
    for (size_t i = 0; i < mc.size(); ++i) {
        for (p = (unsigned char*)mc[i].c_str(); *p != '\0'; p++) { //try static_cast
            h = multiplier * h + *p;
        }
    }
    return h % sz;
}


Suffix& my_map::operator[](Prefix& pref) {
    pair* temp;
    size_t h = hash(pref);
    for (temp = hashtab[h]; temp != nullptr; temp = temp->next) {
        if (temp->first == pref)
            return temp->second;
    }
    temp = new pair{};
    temp->first = pref;
    Suffix dss;
    temp->next = hashtab[h];
    hashtab[h] = temp;
    return temp->second;
}