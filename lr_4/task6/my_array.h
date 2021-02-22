#ifndef MY_ARRAY
#define MY_ARRAY

#include <string>
using namespace std;

typedef class my_array Suffix;
typedef class my_array Prefix;


class my_array {
    string* arr;
    size_t sz;
    size_t pos;
    int multilpier;
public:
    my_array();
    ~my_array();
    void push_back(const string& s);
    void pop_front();
    size_t size() const;
    string& operator[](size_t index);
    bool operator==(my_array&);
    my_array& operator=(my_array&);
};


#endif