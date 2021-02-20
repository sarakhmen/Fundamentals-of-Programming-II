#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 100

typedef struct Queue Queue;
typedef struct Node Node;
Queue *new_queue();
void push(Queue *queue, int new_val);
int pull(Queue *queue);

struct Node{
	int val;
	Node *next;
};

struct Queue{
	int empty;
	Node *tail;
	Node *head;
};


Queue *new_queue(){
	Queue* new_q = (Queue*)malloc(sizeof(Queue));
	new_q->empty = 1;
	Node *node = (Node*)malloc(sizeof(Node));
	new_q->head = node;
	new_q->tail = node;
	for(int i =0; i<99; ++i){
		node->next = (Node*)malloc(sizeof(Node));
		node = node->next;
	}
	node->next = new_q->head;
	return new_q;
}


void push(Queue *queue, int new_val){
	if((queue->head == queue->tail) && (queue->empty == 0)){
		printf("c_queue is full\n");
		return;
	}
	queue->head->val = new_val;
	queue->head = queue->head->next;
	if(queue->head == queue->tail)
		queue->empty = 0;
}


int pull(Queue *queue){
	if((queue->head == queue->tail) && (queue->empty == 1)){
		printf("c_queue is empty\n");
		return INT_MAX;
	}
	int ret_value = queue->tail->val;
	queue->tail = queue->tail->next;
	if(queue->tail == queue->head)
		queue->empty = 1;
	return ret_value;
}


int main(void){
	Queue *queue = new_queue();
	for(int i = 0; i < 3; ++i){
		printf("adding %d to the c_queue\n", i);
		push(queue, i);
	}
	for(int i = 0; i < 4; ++i){
		int num = pull(queue);
		if(num==INT_MAX)
			printf("failed to pull\n");
		else
			printf("num %d successfully pulled\n", num);
	}
	printf("trying to fill the c_queue with 101 nums\n");
	for(int i = 0; i < 101; ++i){
		push(queue, i);
	}
	return 0;
}