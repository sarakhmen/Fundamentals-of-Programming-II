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
Nameval *partition(Nameval* listp, int (*fn)(Nameval*, void*), void *arg);
int lesser_value(Nameval*, void*);
Nameval *merge(Nameval* listp1, Nameval* listp2);
Nameval *insert(Nameval* listp, Nameval* elem, Nameval* newp, int before);
Nameval *reverse_iter(Nameval* listp);
Nameval *reverse_rec(Nameval* listp);
void freeall(Nameval *listp);
Nameval *delitem(Nameval *listp, char *name);
void test_reverse_func(Nameval* (*reverse_func)(Nameval* listp));


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

Nameval *partition(Nameval* listp, int (*fn)(Nameval*, void*), void *arg){
	if(listp==NULL)
		return NULL;
	Nameval *left,
			*right,
			*next,
			*temp;
	left = listp;
	right = listp;
	next = listp->next;
	listp->next=NULL;
	while(next!=NULL){
		temp = next->next;
		if(fn(next, arg))
			left = addfront(left, next);
		else
		{
			right->next = next;
			right = right->next;
		}
		next = temp;
	}
	right->next = NULL;
	return left;
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

Nameval *reverse_rec(Nameval* listp){
	if(listp == NULL)
		return NULL;
	if(listp->next){
		Nameval* temp = reverse_rec(listp->next);
       	listp->next->next = listp;
       	listp->next = NULL;
       	return temp;
   	}
   	else
    	return listp;
}

Nameval *reverse_iter(Nameval* listp){
	Nameval *temp1,
			*temp2,
			*temp3;
	temp1 = listp;
	temp2 = NULL;
	temp3 = NULL;
	while(temp1 != NULL){
		temp2 = temp1;
		temp1 = temp1->next;
		temp2->next = temp3;
		temp3 = temp2;
	}
	return temp2;
}

void freeall(Nameval *listp){
	Nameval *next;
	for(; listp != NULL; listp = next){
		next = listp->next;
		free(listp->name);
		free(listp);
	}
}


Nameval *delitem(Nameval *listp, char *name){
	Nameval *p, *prev;
	prev = NULL;
	for(p = listp; p != NULL; p = p->next){
		if(strcmp(name, p->name) == 0){
			if(prev == NULL)
				listp = p->next;
			else
				prev->next = p->next;
			free(p->name);
			free(p);
			return listp;
		}
		prev = p;
	}
	printf("delitem: %s not in list\n", name);
	return NULL;
}


void test_reverse_func(Nameval* (*reverse_func)(Nameval* listp)){
	FILE* fin;
	if((fin = fopen("test_reverse_func.txt", "r")) == NULL){
		fprintf(stderr, "Error while opening!\n");
		exit(1);
	}
	int i = 0,	
		k = 0;
	int value;
	char str[50];
	printf("<Test start>\n\n");
	Nameval* list = NULL;
	while(fscanf(fin, "%d", &i) != EOF){
		printf("Case %d:\n", ++k);
		printf("\nInput:\n");
		
		for(int j = i; j>0; --j){
			fscanf(fin, "%s", str);
			fscanf(fin, "%d", &value);
			printf("%s %d\n", str, value);
			list = addend(list, newitem(str, value));
		}
		printf("\nExpected:\n");
		for(int j = i; j>0; --j){
			fscanf(fin, "%s", str);
			fscanf(fin, "%d", &value);
			printf("%s %d\n", str, value);
		}
		list = reverse_func(list);
		printf("\nResult:\n");
		print_ls(list);
		printf("\n\n");
		freeall(list);
		list = NULL;
	}
	printf("\n<End of test>\n");
	fclose(fin);
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
	// print_ls(nvlist);
	// printf("\n");
	// delitem(nvlist, "asdf");
	// nvlist = reverse_rec(nvlist);
	// print_ls(nvlist);
	// printf("\n");
	// freeall(nvlist);
	// nvlist = reverse_iter(nvlist);
	// print_ls(nvlist);

	test_reverse_func(reverse_iter);
	return 0;
}