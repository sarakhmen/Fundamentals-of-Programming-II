#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;

Nameval *lookup(Nameval *treep, char *name);
Nameval *insert(Nameval *treep, Nameval *newp);
Nameval *nrlookup(Nameval *treep, char *name);
void applyinorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg);
void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg);
void printnv(Nameval *p, void *arg);
void test_applyinorder();
void test_lookup(Nameval *(*lookup)(Nameval *, char *));
void test_insert();
void inorder_write_value(Nameval* node, void* arr);
void postorder_write_value(Nameval* node, void* arr);
void test_applypostorder();

struct Nameval {
	char *name;
	int value;
	Nameval *left;
	Nameval *right;
};

Nameval *lookup(Nameval *treep, char *name){
	if(treep == NULL)
		return NULL;
	int cmp = strcmp(name, treep->name);
	if(cmp == 0)
		return treep;
	else if (cmp < 0)
		return lookup(treep->left, name);
	else 
		return lookup(treep->right, name);
}

Nameval *nrlookup(Nameval *treep, char *name){
	while(treep != NULL){
		int cmp = strcmp(name, treep->name);
		if(cmp == 0)
			return treep;
		else if (cmp < 0)
			treep = treep->left;
		else
			treep = treep->right;
	}
	return NULL;
}

Nameval *insert(Nameval *treep, Nameval *newp){
	if(treep == NULL)
		return newp;
	int cmp = strcmp(newp->name, treep->name);
	if(cmp == 0)
		printf("insert: duplicate entry %s ignored", newp->name);
	else if(cmp < 0)
		treep->left = insert(treep->left, newp);
	else 
		treep->right = insert(treep->right, newp);
	return treep;
}

void applyinorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg){
	if(treep == NULL)
		return;
	applyinorder(treep->left, fn, arg);
	(*fn)(treep, arg);
	applyinorder(treep->right, fn, arg);
}

void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*), void *arg){
	if(treep == NULL)
		return;
	applypostorder(treep->left, fn, arg);
	applypostorder(treep->right, fn, arg);
	(*fn)(treep, arg);
}

void printnv(Nameval *p, void *arg){
	char *fmt;
	fmt = (char *) arg;
	printf(fmt, p->name, p->value);
}

void test_insert(){
	Nameval* treep = NULL;
	treep = insert(treep, &(Nameval){"TestValue1", 10, NULL, NULL});
	treep = insert(treep, &(Nameval){"TestValue2", 100, NULL, NULL});
	treep = insert(treep, &(Nameval){"TestValue3", 1000, NULL, NULL});
	if(strcmp(lookup(treep, "TestValue1")->name, "TestValue1") != 0 
		|| strcmp(lookup(treep, "TestValue2")->name, "TestValue2") != 0
		|| strcmp(lookup(treep, "TestValue3")->name, "TestValue3") != 0
		)
		printf("<test_insert()> Error occurred\n");
	else
		printf("<test_insert()> Successful\n");
}

void test_lookup(Nameval *(*lookup)(Nameval *, char *)){
	Nameval *treep = &(Nameval){"TestValue1", 10, NULL, NULL};
	treep->left = &(Nameval){"TestValue0", 100, NULL, NULL};
	treep->right = &(Nameval){"TestValue2", 1000, NULL, NULL};
	if(lookup(treep, "TestValue1") != treep 
		|| lookup(treep, "TestValue0") != treep->left
		|| lookup(treep, "TestValue2") != treep->right
		|| lookup(treep, "BadValue") != NULL)
		printf("<test_lookup()> Error occurred\n");
	else
		printf("<test_lookup()> Successful\n");
}

void inorder_write_value(Nameval* node, void* arr){
	static int i = 0;
	int *int_arr = (int*)arr;
	int_arr[i++] = node->value;
}

void postorder_write_value(Nameval* node, void* arr){
	static int i = 0;
	int *int_arr = (int*)arr;
	int_arr[i++] = node->value;
}

void test_applyinorder(){
	Nameval* treep = NULL;
	treep = insert(treep, &(Nameval){"D", 1, NULL, NULL});
	treep = insert(treep, &(Nameval){"B", 2, NULL, NULL});
	treep = insert(treep, &(Nameval){"C", 3, NULL, NULL});
	treep = insert(treep, &(Nameval){"A", 4, NULL, NULL});
	treep = insert(treep, &(Nameval){"F", 5, NULL, NULL});
	treep = insert(treep, &(Nameval){"E", 6, NULL, NULL});
	treep = insert(treep, &(Nameval){"G", 7, NULL, NULL});
	int inorder_arr[7];
	int check_arr[7] = {4, 2, 3, 1, 6, 5, 7};
	applyinorder(treep, inorder_write_value, inorder_arr);
	for(int i = 0; i<7; ++i)
		if(inorder_arr[i]!=check_arr[i]){
			printf("<test_applyinorder()> Error occurred\n");
			return;
		}
	printf("<test_applyinorder()> Successful\n");
}

void test_applypostorder(){
	Nameval* treep = NULL;
	treep = insert(treep, &(Nameval){"D", 1, NULL, NULL});
	treep = insert(treep, &(Nameval){"B", 2, NULL, NULL});
	treep = insert(treep, &(Nameval){"C", 3, NULL, NULL});
	treep = insert(treep, &(Nameval){"A", 4, NULL, NULL});
	treep = insert(treep, &(Nameval){"F", 5, NULL, NULL});
	treep = insert(treep, &(Nameval){"E", 6, NULL, NULL});
	treep = insert(treep, &(Nameval){"G", 7, NULL, NULL});
	int postorder_arr[7];
	int check_arr[7] = {4, 3, 2, 6, 7, 5, 1};
	applypostorder(treep, postorder_write_value, postorder_arr);
	for(int i = 0; i<7; ++i)
		if(postorder_arr[i]!=check_arr[i]){
			printf("<test_applypostorder()> Error occurred\n");
			return;
		}
	printf("<test_applypostorder()> Successful\n");
}

int main(void){
	test_insert();
	test_lookup(lookup);
	test_lookup(nrlookup);
	test_applyinorder();
	test_applypostorder();
	return 0;
}