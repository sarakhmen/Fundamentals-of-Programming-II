#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;

Nameval *newitem(char *name, int value);
Nameval *addfront(Nameval *listp, Nameval *newp);
Nameval *addend(Nameval *listp, Nameval *newp);
void print_ls(Nameval *listp);
void coolfun(Nameval *listp, void (*fn)(Nameval*, void*), void *arg);
void count_value(Nameval* node, void *arg);
Nameval *copy(Nameval *dest, Nameval *source);
Nameval* partition(Nameval** listp, int (*fn)(Nameval*, void*), void* arg);
int lesser_value(Nameval*, void*);
Nameval *merge(Nameval* listp1, Nameval* listp2);
Nameval *insert(Nameval* listp, Nameval* elem, Nameval* newp, int before);

struct Nameval {
	char *name;
	int value;
	Nameval *next;
};

Nameval *newitem(char *name, int value){
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

void print_ls(Nameval *listp){
	for(; listp != NULL; listp = listp->next)
		printf("%s %d\n", listp->name, listp->value);
}

void coolfun(Nameval *listp, void (*fn)(Nameval*, void*), void *arg){
	for(; listp != NULL; listp = listp->next)
		fn(listp, arg);
}

void count_value(Nameval* node, void *arg){
	*(int*)arg += node->value;
}

Nameval* copy(Nameval *dest, Nameval *source){
	Nameval* prev,
			*ret_value = dest;
	if(dest == NULL)
		return NULL;
	for(; source!=NULL; source = source->next){
		if(dest == NULL){
			prev->next = newitem(source->name, source->value);
			prev = prev->next;
		}
		else {
			prev = dest;
			int len = strlen(source->name);
			char *temp;
			temp = (char*)realloc(dest->name, (len+1)*sizeof(char));
			if(temp == NULL)
				continue;
			memcpy(dest->name, source->name, len+1);
			dest->value = source->value;
			dest = dest->next;
		}
	}
	return ret_value;
}

Nameval* partition(Nameval** listp, int (*fn)(Nameval*, void*), void* arg) {
	//ділить елементи масиву на дві частини(яка відповідає умові функції fn, і яка – ні)
	if (*listp == NULL)
		return NULL;
	Nameval* border = *listp,
		* right = (*listp)->next,
		* prev = *listp;
	while (right != NULL) {
		if (fn(right, arg)) {
			right = right->next;
			*listp = addfront(*listp, prev->next);
			prev->next = right;
		}
		else {
			prev = right;
			right = right->next;
		}
	}
	if (fn(border, arg))
		border = border->next;
	return border;
}


int lesser_value(Nameval* node, void* arg){
	return (node->value < *(int*)arg);
}


Nameval *merge(Nameval* listp1, Nameval* listp2){
	return addend(listp1, listp2);
}

Nameval *insert(Nameval* listp, Nameval* elem, Nameval* newp, int before){
	if(listp==NULL)
		return NULL;
	if(newp == NULL)
		return listp;
	Nameval *p;
	if(before){
		if(listp == elem){
			newp->next = listp;
			return newp;
		}
		for(p = listp; p->next!=NULL; p = p->next){
			if(p->next == elem)
				break;
		}
		if(p->next != NULL){
			newp->next = p->next;
			p->next = newp;
		}
	}
	else {
		for(p = listp; p!=NULL; p = p->next){
			if(p == elem)
				break;
		}
		if(p != NULL){
			newp->next = p->next;
			p->next = newp;
		}
	}
	return listp;
}


int main(void){
	// Nameval *nvlist = NULL;
	// Nameval* ata = newitem("ata", 1);
	// nvlist = addfront(nvlist, ata);
	// nvlist = insert(nvlist, ata, newitem("before", 2), 1);
	// nvlist = insert(nvlist, ata, newitem("after", 2), 0);
	// nvlist = insert(nvlist, ata, newitem("qweqw", 2), 0);
	// nvlist = insert(nvlist, ata, newitem("asdf", 2), 0);
	// nvlist = insert(nvlist, ata, newitem("zxcv", 2), 0);
	// nvlist = insert(nvlist, ata, newitem("hello", 2), 0);
	// addend(nvlist, newitem("ddsta", 0));
	// addend(nvlist, newitem("dawqweta", -1));
	// addend(nvlist, newitem("dqweta", 0));
	// addend(nvlist, newitem(NULL, -1));	
	// nvlist = addfront(nvlist, newitem("data", 1));
	// nvlist = insert(nvlist, ata, newitem("before", 2), 1);
	// nvlist = insert(nvlist, ata, newitem("after", 2), 0);
	// int amount = 0;
	// coolfun(nvlist, count_value, &amount);
	// printf("The number value1 = %d\n", amount);
	// print_ls(nvlist);
	// printf("\n");
	// Nameval *newlist = NULL;
	// newlist = addend(newlist, newitem("kaka", 1));
	// newlist = addend(newlist, newitem("sdaf", 0));
	// newlist = addend(newlist, newitem("kadfka", 0));
	// newlist = addend(newlist, newitem("faka", -1));
	// newlist = copy(newlist, nvlist);
	// amount = 0;
	// coolfun(newlist, count_value, &amount);
	// printf("The number value2 = %d\n", amount);
	// print_ls(newlist);
	// nvlist = addend(nvlist, newitem("kaka", -1));
	// nvlist = addend(nvlist, newitem("sdaf", -1));
	// nvlist = addend(nvlist, newitem("kadfka", 1));
	// nvlist = addend(nvlist, newitem("faka", -1));
	// Nameval *p = partition(NULL, lesser_value, (int[]){0});
	// amount = 0;
	// coolfun(p, count_value, &amount);
	// printf("The number value3 = %d\n", amount);
	// print_ls(p);
	// nvlist = merge(nvlist, newlist);
	// 	printf("\n");
	// print_ls(nvlist);
	return 0;
}
