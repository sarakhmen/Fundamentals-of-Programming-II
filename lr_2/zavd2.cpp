#include <iostream>
#include <iomanip>
using namespace std;

int main(void){
	double meters;
	char proceed = 0;
	cout << fixed << setprecision(1);
	while(proceed != '0'){
		cout << "Enter the number of meters to convert to feet and inches: ";
		cin >> meters;
		if(cin.fail()){
			cout << "Error occurred!" << endl;
			cin.clear();
		}
		else{
			cout << "Ther nubmer of feet is " << meters*3.281 << endl;
			cout << "Ther nubmer of inches is " << meters*3.281*12 << endl;
		}
		cin.ignore(32767, '\n');
		cout << "Wanna continue? Enter 0 to quit" << endl;
		cin >> proceed;
		cin.ignore(32767, '\n');
	}
	cout << "End" << endl;
	return 0;
}