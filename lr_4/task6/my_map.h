#ifndef MY_MAP
#define MY_MAP

#include "my_array.h"


class my_map {
    struct pair {
        Prefix first;
        Suffix second;
        pair* next;
        ~pair();
    };

    size_t sz;
    pair** hashtab;
    int multiplier;
public:
    my_map();
    ~my_map();
    size_t hash(Prefix&);
    Suffix& operator[](Prefix&);
};

#endif