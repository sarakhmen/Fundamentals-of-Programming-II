#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

class time_and_date{
	char *time_date;
public:
	time_and_date(const char* str);
	~time_and_date();
	void show();
};

time_and_date::time_and_date(const char* str){
	time_date = (char *)malloc((strlen(str)+1)*sizeof(char));
	if(!time_date){
		cout << "Allocation error" << endl;
		exit(1);
	}
	strcpy(time_date, str);
}

time_and_date::~time_and_date(){
	free(time_date);
}

void time_and_date::show(){
	cout << time_date;
}


int main(void){
	time_t cur_t = time(NULL);
	time_and_date td(ctime(&cur_t));
	td.show();
	return 0;
}