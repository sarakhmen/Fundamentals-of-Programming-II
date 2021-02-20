#include <iostream>
#define LIGHT_SPEED 186000
using namespace std;


class planet{
    int moons;
    double dist_from_sun;
    double diameter;
    double mass;
public:
    planet(int mns, double dst, double dm, double ms):
        moons(mns), dist_from_sun(dst), diameter(dm), mass(ms) {}
    double get_mass() {return mass;}
    double get_diameter() {return diameter;}
    double get_miles() {return dist_from_sun;}
};

double light(planet plnt){
    return plnt.get_miles() / LIGHT_SPEED;
}

int main(){
    planet plnt(2, 42312342.2, 15492.542, 2.842e+27);
    cout << "Light reaches the planet in " << light(plnt) << " seconds" << endl;
    return 0;
}