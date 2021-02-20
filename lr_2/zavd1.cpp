#include <iostream>
#include <cstring>
#define NAME_SIZE 30
using namespace std;

class Staff {
	unsigned payment;
	unsigned hours;
	char name[NAME_SIZE];
public:
	Staff();
	Staff(char* n, unsigned h, unsigned p);
	unsigned get_salary();
	char *get_name();
};

Staff::Staff()
{

};

Staff::Staff(char* n, unsigned h, unsigned p){
	if(n == NULL || strlen(n)>= NAME_SIZE){
		printf("ERROR: improper name!\n");
		exit(1);
	}
	strcpy(name, n);
	hours = h;
	payment = p;
}

unsigned Staff::get_salary(){
	return payment*hours;
}

char *Staff::get_name(){
	return name;
}


int main(void){
	char names[10][10] = {"Billy", "Bob", "Kate", "George", "Sindy", "Lara",
						"Mike", "Angel", "Dan", "Sara"};
	Staff personal[10];
	unsigned payment;
	unsigned hours;
	for(int i = 0; i<10; ++i){
		cout << "Enter payment and number of hours for " << names[i] << ':' << endl;
		cin >> payment >> hours;
		if(cin.fail()){
			cout << "ERROR: improper input. Try again" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			--i;
		}
		else {
			Staff person(names[i], hours, payment);
			personal[i] = person;
		}
	}
	unsigned sum = 0;
	for(int i = 0; i<10; ++i){
		cout << "Salary of " << personal[i].get_name() << '=' << personal[i].get_salary() << endl;
		sum += personal[i].get_salary();
	}
	cout << "Total salary of all staff = " << sum << endl;
	return 0;
}