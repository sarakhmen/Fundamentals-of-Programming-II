#include <iostream>
using namespace std;

class samp{
    int i, j;
public:
    ~samp(){ cout << "destructing (i = " << i << ", j = " << j << ")\n";}
    void set_ij(int i, int j) { this->i = i; this->j = j;}
    int get_product() { return i*j;}
};


int main(){
    samp *ptr;
    ptr = new samp[10];
    for(int i = 0; i<10; i++)
        ptr[i].set_ij(i, i);
    for(int i = 0; i < 10; i++){
        cout << "Product [" << i << "] is: ";
        cout << ptr[i].get_product() << "\n";
    }
    delete[] ptr;
    return 0;
}