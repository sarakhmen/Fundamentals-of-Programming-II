#include <iostream>
#include <ctime>

using namespace std;

ostream &tdm(ostream &stream){
    time_t t = time(NULL);
    tm *timeinfo = gmtime(&t);
    stream << asctime(timeinfo);
    free(timeinfo);
    return stream;
}

int main(){
    cout << tdm << endl;
    return 0;
}