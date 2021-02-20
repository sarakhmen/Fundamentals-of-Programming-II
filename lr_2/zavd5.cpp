#include <iostream>
#include <bits/stdc++.h>
#define SIZE 100

using namespace std;

class q_type {
	int queue[SIZE];
	int head, tail;
	bool reversed_behavior;
public:
	q_type();
	void q(int num);
	int deq();
};

q_type::q_type(){
	head = tail = 0;
	reversed_behavior = false;
};

void q_type::q(int num){
	if((head == tail) && reversed_behavior == true){
		cout << "queue is full" << endl;
		return;
	}
	queue[head++] =num; 
	if(head == SIZE){
		head = 0;
		reversed_behavior = !reversed_behavior;
	}
}

int q_type::deq(){
	if((head == tail) && reversed_behavior == false){
		cout << "queue is empty" << endl;
		return INT_MAX;	//to determine if the queue is empty
	}
	int ret_val = queue[tail++];
	if(tail == SIZE){
		tail = 0;
		reversed_behavior = !reversed_behavior;
	} 
	return ret_val;
}


int main(void){
	q_type queue;
	for(int i = 0; i < 3; ++i){
		cout << "adding " << i << " to the queue" << endl;
		queue.q(i);
	}
	for(int i = 0; i < 4; ++i){
		int num = queue.deq();
		if(num==INT_MAX)
			cout << "failed to pull" << endl;
		else
			cout << "num " << num << " successfully pulled" << endl;
	}
	cout << "trying to fill the queue with 101 nums" << endl;
	for(int i = 0; i < 101; ++i){
		queue.q(i);
	}
	return 0;
}