#include <iostream>
#include <cmath>

using namespace std;

double root(double num);
int root(int num);
long root(long num);

double root(double num){
	cout << "(inside double func) ";
	if(num<0)
		return 0;
	else
		return sqrt(num);
}

int root(int num){
	cout << "(inside int func) ";
	if(num<0)
		return 0;
	else
		return (int)sqrt(num);
}


long root(long num){
	cout << "(inside long func) ";
	if(num<0)
		return 0;
	else
		return (long)sqrtl(num);
}


int main(void){
	cout << "root of 1000 = " << root(1000) << endl;
	cout << "root of 1000L = " << root(1000L) << endl;
	cout << "root of 1000.0 = " << root(1000.0) << endl;
	return 0;
}