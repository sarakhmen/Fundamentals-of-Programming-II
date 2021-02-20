#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

class Area{
public:
    double height;
    double width;
};

class Rectangle: public Area{
public:
    Rectangle(double width, double height);
    double area();
};

class Isosceles: public Area{
public:
    Isosceles(double side, double base);
    double area();
};

class Cylinder: public Area{
public:
    Cylinder(double radius, double height);
    double area();
};

Rectangle::Rectangle(double width, double height){
    Area::height = height;
    Area::width = width;
}

double Rectangle::area(){
    return height*width;
}

Isosceles::Isosceles(double side, double base){
    height = side;
    width = base;
}

double Isosceles::area(){
    return (width*sqrt((height + width/2)*(height - width/2)))/2;
}

Cylinder::Cylinder(double radius, double height){
    Area::height = height;
    width = radius;
}

double Cylinder::area(){
    return 2*M_PI*width*width + M_PI*2*width*height;
}

int main(){
    Rectangle r(2.5, 5.0);
    Isosceles tr(10.0, 5.0);
    Cylinder c(10.5, 21.8);
    cout << "the area of ​​the rectangle is " << r.area() << endl;
    cout << "the area of the isosceles is " << tr.area() << endl;
    cout << "the area of the cylinder is " << c.area() << endl;
    return 0;
}