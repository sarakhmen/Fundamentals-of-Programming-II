#include <iostream>
#include <ctime>
using namespace std;

void sleep(int);
void sleep(const char *);

int main(void){
	cout << "clock() = " << clock() << endl;
	cout << "sleep(10000)" << endl;
	sleep(10000);
	cout << "clock() = " << clock() << endl;
	cout << "sleep(\"10000\")" << endl;
	sleep("10000");
	cout << "clock() = " << clock() << endl;
	return 0;
}

void sleep(int msec){
	int CLOCKS_PER_MSEC = CLOCKS_PER_SEC / 1000;
	clock_t end = clock() + msec*CLOCKS_PER_MSEC;
	while(clock() < end){}
}

void sleep(const char* ms_str){
	int CLOCKS_PER_MSEC = CLOCKS_PER_SEC / 1000;
	int msec = atoi(ms_str);
	clock_t end = clock() + msec*CLOCKS_PER_MSEC;
	while(clock() < end){}
}