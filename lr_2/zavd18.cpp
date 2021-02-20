#include <iostream>
using namespace std;

class mybox{
	double vol;
public:
	mybox(double a, double b, double c);
	void volume();
};

mybox::mybox(double a, double b, double c){
	if(a < 0 || b < 0 || c < 0){
		cout << "Wrong arguments!" << endl;
		exit(1);
	}
	vol = a*b*c;
}

void mybox::volume(){
	cout << "The volume of the parallelepiped = " << vol << endl;
}

int main(){
	mybox(10.4, 4.5, 8.9).volume();
	return 0;
}