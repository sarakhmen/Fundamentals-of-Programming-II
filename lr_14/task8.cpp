// #include <iostream>
// using namespace std; 
  
// class Compl
// { 
//     double real; 
//     double imag;   
// public: 
//     Compl(double r = 0.0, double i = 0.0) : real(r), imag(i) {} 
//     bool operator == (Compl rhs) { 
//        return (real == rhs.real && imag == rhs.imag)? true : false; 
//     } 
// }; 
  
// int main() 
// { 
//     Compl com1(3.0, 0.0); 
  
//     if (com1 == 3.0) 
//        cout << "Same"; 
//     else
//        cout << "Not Same"; 
//      return 0; 
// }


#include <iostream>
using namespace std; 
  
class Compl
{ 
    double real; 
    double imag;   
public: 
    explicit Compl(double r = 0.0, double i = 0.0) : real(r), imag(i) {} 
    bool operator == (Compl rhs) { 
       return (real == rhs.real && imag == rhs.imag)? true : false; 
    } 
}; 
  
int main() 
{ 
    Compl com1(3.0, 0.0); 
  
    if (com1 == Compl(3.0)) 
       cout << "Same"; 
    else
       cout << "Not Same"; 
     return 0; 
}