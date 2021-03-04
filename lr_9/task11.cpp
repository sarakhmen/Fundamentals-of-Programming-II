#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class strtype {
    char *p;
    int len;
public:
    strtype(const char *ptr);
    ~strtype() { delete [] p; }
    friend istream &operator >>(istream &stream, strtype &obj);
    friend ostream &operator <<(ostream &stream, strtype &obj);
};

strtype::strtype(const char *ptr) {
    len = strlen(ptr)+1;
    p = new char(len);
    if (!p) {
        cout << "Allocation error\n";
        exit(1);
    }

    strcpy(p, ptr);
}

// Create operator << inserter function here.
ostream &operator <<(ostream &stream, strtype &obj){
    stream << obj.p;
    return stream;
}

istream &operator >>(istream &stream, strtype &obj){ 
    stream.getline(obj.p, obj.len);
    // stream.sync();
    return stream;
}

int main() {
    strtype s1("This is a test."), s2("I hate C++!");
    cout << "enter two strings: " << endl;
    cin >> s1 >> s2;
    cout << s1 << '\n' << s2 << '\n';
    return 0;
}