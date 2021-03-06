#include <iostream>
using namespace std;

istream &skipchar(istream &stream){
    bool read = true;
    char ch;
    while(true){   
        for (int i = 0; i < 5; i++)
        {
            ch = stream.get();
            if(ch == '\n')
                return stream;
            if (read) 
                cout << ch;
        }
        read = !read;
    }
}


int main(){
    cin >> skipchar;
    return 0;
}