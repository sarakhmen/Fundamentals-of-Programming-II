#include <iostream>
#include <ctime>
using namespace std;

class watch{
    time_t seconds;
public:
    watch(){seconds = time(NULL);}
    void update(){seconds = time(NULL);}
    friend ostream &operator <<(ostream &stream, watch &obj){
        tm *timeinfo = gmtime(&obj.seconds);
        stream << asctime(timeinfo);
        free(timeinfo);
        return stream;
    }
};

int main(){
    watch wc;
    cout << wc << endl;
    return 0;
}