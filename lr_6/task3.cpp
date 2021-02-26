#include <iostream>
using namespace std;
class myclass {
public:
 myclass();
 myclass(const myclass &obj);
 myclass f();
 myclass g(myclass obj);
};
// Normal constructor
myclass::myclass() {
 cout << "Constructing normally\n";
}
// Copy constructor
myclass::myclass(const myclass &obj) {
 cout << "Constructing copy\n";
}
// Return an object.
myclass myclass::f() {
 myclass temp;
 return temp;
}
myclass myclass::g(myclass obj) {
 myclass temp = obj;
 return temp;
}
int main() {
 myclass obj;
 obj = obj.f();
 obj = obj.g(obj);
 return 0;
}

/* Коли створюється новий об'єкт класу myclass відбувається виклик звичайного
конструктора. Подібне наблюдаємо в першій стрічці коду функції main та всередині
функції f(). Конструктор копій викликається, коли ми передаємо об'єкт в якості 
аргументу в функцію g() та коли в цій ж функції створюється новий об'єкт наступною
стрічкою коду: myclass temp = obj */