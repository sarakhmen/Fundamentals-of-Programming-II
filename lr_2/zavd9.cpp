#include <iostream>
#include <cstdlib>
using namespace std;

int ato(const char* str){
	return atoi(str);
}

long ato(const char* str){
	return atol(str);
}

double ato(const char* str){
	return atof(str);
}

int main(void){
	const char* str = "some str";
	cout << ato(str);
	return 0;
}