#include <iostream>
#include <cstring>

using namespace std;

class strtype {
    int len;
    char* p;
public:
    strtype();
    strtype(char const* s);
    strtype(const strtype&);
    ~strtype() { if(p) delete[] p; }
    char* get_str() { return p; }
    int size() { return len; }
    bool operator >(strtype& str);
    bool operator <(strtype& str);
    bool operator ==(strtype& str);
    char& operator[] (int i);
    strtype& operator =(const strtype& str);
    friend strtype operator +(strtype& str1, strtype& str2);
};

strtype::strtype() {
    len = 0;
    p = nullptr;
}

strtype::strtype(char const* s) {
    len = strlen(s);
    p = new char[len + 1];
    if (!p) {
        cout << "allocation error!";
        exit(1);
    }
    strcpy(p, s);
}

strtype::strtype(const strtype &str) {
    len = strlen(str.p);
    p = new char[len + 1];
    if (!p) exit(1);
    strcpy(p, str.p);
}

strtype& strtype::operator=(const strtype &str) {
    len = strlen(str.p);
    p = new char[len + 1];
    if (!p) exit(1);
    strcpy(p, str.p);
}

char& strtype::operator[](int i) {
    if (i < 0 || i >= len) {
        cout << "Bounds error!";
        exit(1);
    }
    return p[i];
}

strtype operator +(strtype& str1, strtype& str2) {
    strtype temp;
    temp.len = str1.len + str2.len + 1;
    temp.p = new char[temp.len];
    if (!temp.p) exit(1);
    strcpy(temp.p, str1.p);
    strcpy(temp.p + str1.len, str2.p);
    return temp;
}

bool strtype::operator >(strtype& str) {
    return (strcmp(p, str.p) > 0) ? true : false;
}

bool strtype::operator <(strtype& str) {
    return (strcmp(p, str.p) < 0) ? true : false;
}

bool strtype::operator ==(strtype& str) {
    return (strcmp(p, str.p) == 0) ? true : false;
}



int main(void) {
    strtype str1("do "), str2("something"), str3;
    str3 = str1 + str2;
    cout << "(str3 = str1 + str2) = " << str3.get_str() << endl;
    cout << "(str1 > str2) = " << (str1 > str2) << endl;
    cout << "(str1 < str2) = " << (str1 < str2) << endl;
    cout << "(str1 == str2) = " << (str1 == str2) << endl;

    return 0;
}

