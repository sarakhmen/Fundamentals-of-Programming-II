#include <iostream>
using namespace std;

char min(char a, char b);
int min(int a, int b);
double min(double a, double b);

char min(char a, char b){
	cout << "(in char min) ";
	return a<b?a:b;
}

int min(int a, int b){
	cout << "(in int min) ";
	return a<b?a:b;
}

double min(double a, double b){
	cout << "(in double min) ";
	return a<b?a:b;
}

int main(void){
	cout << "minimum CHAR among 'A' and 'B' = " << min('A', 'B') << endl;
	cout << "minimum INT among -5 and 10 = " << min(-5, 10) << endl;
	cout << "minimum DOUBLE among 0.001 and 0.0005 = " << min(0.001, 0.0005) << endl;
	return 0;
}