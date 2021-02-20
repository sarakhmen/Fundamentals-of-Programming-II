#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;

Nameval *newitem(char *name, void *value);
Nameval *addfront(Nameval *listp, Nameval *newp);
Nameval *addend(Nameval *listp, Nameval *newp);
void print_int_ls(Nameval *listp);

struct Nameval {
	char *name;
	void* value;
	Nameval *next;
};

Nameval *newitem(char *name, void* value){
	Nameval *newp;
	newp = (Nameval *) malloc(sizeof(Nameval));
	if(name == NULL){
		newp->name = (char*)malloc(sizeof(char));
		*newp->name	= '\0';
	}
	else {
		int len = strlen(name);
		newp->name = (char*)malloc((len+1)*sizeof(char));
		memcpy(newp->name, name, len+1);
	}
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

void print_int_ls(Nameval *listp){
	for(; listp != NULL; listp = listp->next)
		printf("%s %d\n", listp->name, *(int*)listp->value);
}


int main(void){
	Nameval *nvlist = NULL;
	int val = 10;
	nvlist = addend(nvlist, newitem("int value", (void*)&val));
	double val2 = 99.99;
	nvlist = addend(nvlist, newitem("double value", (void*)&val2));
	for(;nvlist!=NULL; nvlist = nvlist->next)
		if(strcmp(nvlist->name,"int value")==0)
			printf("%s %d\n", nvlist->name, *(int*)nvlist->value);
		else if(strcmp(nvlist->name,"double value")==0)
			printf("%s %.2lf\n", nvlist->name, *(double*)nvlist->value);
	return 0;
}