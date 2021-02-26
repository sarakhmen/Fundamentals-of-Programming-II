#include <iostream>
#include <ctime>

using namespace std;
void pause(int dur);

class stopwatch{
	bool started;
	clock_t time_of_creation;
	clock_t start_time;
	double passed_sec;
public:
	stopwatch();
	stopwatch(clock_t);
	~stopwatch();
	void start();
	void stop();
	void show();
};

stopwatch::stopwatch(){
	time_of_creation = clock();
	passed_sec = 0;
	started = 0;
}

stopwatch::stopwatch(clock_t t){
	time_of_creation = t;
	passed_sec = 0;
	started = 0;
}

stopwatch::~stopwatch(){
	cout << "Time passed since creation of stopwatch = " 
		 << (double)(clock() - time_of_creation) / CLOCKS_PER_SEC << endl;
}

void stopwatch::start(){
	if(started)
		cout << "stapwatch is already started" << endl;
	else {
		start_time = clock();
		started = true;
	}
}

void stopwatch::stop(){
	if(!started)
		cout << "stopwatch has not started yet" << endl;
	else{
		passed_sec += (double)(clock() - start_time) / CLOCKS_PER_SEC;
		started = false;
	}
}

void stopwatch::show(){
	if(started)
		cout << "elapsed time = " << passed_sec + (double)(clock() - start_time)/ CLOCKS_PER_SEC << endl;
	else
		cout << "elapsed time = " << passed_sec << endl;
}


int main(void){
	stopwatch timer(clock());
	timer.start();
	pause(5);
	timer.show();
	timer.start();
	pause(3);
	timer.stop();
	timer.show();
	timer.stop();
	timer.start();
	pause(5);
	timer.stop();
	timer.show();
	return 0;
}


void pause(int dur){
	int temp = time(NULL) + dur;
	while(temp > time(NULL));
}
