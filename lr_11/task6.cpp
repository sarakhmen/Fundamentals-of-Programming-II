#include <iostream>
using namespace std;

class Dist{
public:
    double distance;
    Dist(double x1, double x2){distance = x2-x1;}
    virtual void trav_time(){
        cout << distance/60 << 'h' << endl;
    }
};

class Metric : public Dist{
public:
    Metric(double x1, double x2): Dist(x1, x2) {}
    void trav_time(){
        cout << distance/100 << 'h' << endl;
    }
};

int main(){
    Dist *p;
    Dist st(10, 400);
    Metric mc(10, 400);
    p = &st;
    p->trav_time();
    p = &mc;
    p->trav_time();
    return 0;
}