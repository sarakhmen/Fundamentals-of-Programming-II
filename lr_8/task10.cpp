#include <iostream>
using namespace std;

class planet {
protected:
    double distance ; // miles from the sun
    int revolve ; // in days
public:
    planet(double d, int r) { distance = d; revolve = r; }
};

class earth : public planet {
    double circumference; // circumference(окружность) of orbit
public:
    earth(double d, int r): planet(d, r) {circumference = 2*r*3.1416;}
    void show(){
        cout << "Distance: " << distance << endl;
        cout << "Revolve: " << revolve << endl;
        cout << "Circumference: " << circumference << endl;
    }
};

int main() {
 earth obj(93000000, 365);
 obj.show();
 return 0;
}