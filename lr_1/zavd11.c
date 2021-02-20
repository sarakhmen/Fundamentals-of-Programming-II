#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;

Nameval *newitem(char *name, int value);
Nameval *addfront(Nameval *listp, Nameval *newp);
Nameval *addend(Nameval *listp, Nameval *newp);
void print_ls(Nameval *listp);
Nameval *insert(Nameval* listp, Nameval* elem, Nameval* newp, int before);
void freeall(Nameval *listp);
Nameval *delitem(Nameval *listp, char *name);

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

void freeall(Nameval *listp){
	Nameval *next;
	for(; listp != NULL; listp = next){
		next = listp->next;
		free(listp->name);
		free(listp);
	}
}

Nameval *delitem(Nameval *listp,char *name){
	Nameval *p, *prev;
	prev=NULL;
	for(p=listp; p!=NULL;p=p->next){
	 	if(strcmp(name,p->name)==0){
	      	if(prev==NULL)
	        	listp=p->next;
	      	else 
	      		prev->next=p->next;
			free(p->name);      
			free(p);
			return listp;
	    }
		prev=p;
	}
	printf("delitem:%s not in list",name);
	return NULL;
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

int main(void){
	Nameval *nvlist = NULL;
	Nameval* ata = newitem("ata", 1);
	nvlist = addfront(nvlist, ata);
	nvlist = insert(nvlist, ata, newitem("before", 2), 1);
	nvlist = insert(nvlist, ata, newitem("after", 2), 0);
	nvlist = insert(nvlist, ata, newitem("qweqw", 2), 0);
	nvlist = insert(nvlist, ata, newitem("asdf", 2), 0);
	nvlist = insert(nvlist, ata, newitem("zxcv", 2), 0);
	nvlist = insert(nvlist, ata, newitem("hello", 2), 0);
	print_ls(nvlist);
	printf("\n");
	delitem(nvlist, "asdf");
	nvlist = reverse_rec(nvlist);
	print_ls(nvlist);
	printf("\n");
	freeall(nvlist);
	nvlist = reverse_iter(nvlist);
	print_ls(nvlist);

	return 0;
}