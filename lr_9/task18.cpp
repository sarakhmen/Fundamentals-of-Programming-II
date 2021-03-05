#include <iostream>
using namespace std;

class square{
    int size;
public:
    square(): size(3) {}
    square(int sz): size(sz) {}
    friend ostream &operator <<(ostream &stream, square &obj);
};

ostream &operator <<(ostream &stream, square &obj){
    for(int i = 0; i < obj.size; ++i){
        for(int j = 0; j < obj.size; ++j)
            stream << '*';
        stream << endl;
    }
    return stream;
}


int main(){
    square sq(8);
    cout << sq;
    return 0;
}