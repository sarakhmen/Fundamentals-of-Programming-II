#include <iostream>
#include <cmath>
using namespace std;

int main(void){
	int num, power;
	cout << "Enter two numbers (first will be raised to the power of the second):";
	cin >> num >> power;
	if(cin.fail()){
		cout << "Error while enreting..." << endl;
		return 1;
	}
	cout << num << '^' << power << " = " << pow(num, power) << endl;
	return 0;
}