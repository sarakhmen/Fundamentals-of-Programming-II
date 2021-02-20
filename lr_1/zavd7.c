#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;

Nameval *newitem(char *name, int value);
Nameval *addfront(Nameval *listp, Nameval *newp);
Nameval *addend(Nameval *listp, Nameval *newp);
void print_ls(Nameval *listp);

struct Nameval {
	char *name;
	int value;
	Nameval *next;
};

Nameval *newitem(char *name, int value){
	Nameval *newp;
	newp = (Nameval *) malloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->next = NULL;
	return newp;
}

Nameval *addfront(Nameval *listp, Nameval *newp){
	newp->next = listp;
	return newp;
}


Nameval *addend(Nameval *listp, Nameval *newp){
	if(listp == NULL)
		return newp;
	Nameval *p;
	for(p = listp; p->next != NULL; p = p->next);
	p->next = newp;
	return listp;
}

void print_ls(Nameval *listp){
	for(; listp != NULL; listp = listp->next)
		printf("%s %d\n", listp->name, listp->value);
}

int main(void){
	Nameval *nvlist = NULL;
	nvlist = addfront(nvlist, newitem("data", 10));
	addend(nvlist, newitem("data", 45));
	addend(nvlist, newitem("data", 55));
	addend(nvlist, newitem("data", 66));
	addend(nvlist, newitem("data", 88));
	addend(nvlist, newitem("data", 100));	
	nvlist = addfront(nvlist, newitem("data", 0));
	print_ls(nvlist);
	return 0;
}

