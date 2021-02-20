#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM 10
#define MAX_NAME_LEN 20
#define NHASH 20
#define CHARS 2
#define MULTIPLIER 31

const char chars[CHARS] = "01";
int generation_complexity;


typedef struct Nameval Nameval;
unsigned int hash(char *str);
Nameval* lookup(char *name, int create, int value);
char* generate_name(int max_length);
void apply_all(void(*fn)(Nameval*, void*), void* arg);
void increase_and_print(Nameval*, void*);

struct Nameval{
	char *name;
	int value;
	Nameval *next;
};
Nameval *symtab[NHASH];

unsigned int hash(char *str){
	unsigned int h = 0;
	unsigned char *p;
	for(p = (unsigned char *) str; *p != '\0'; p++)
		h = MULTIPLIER*h + *p;
	return h % NHASH;
}

Nameval* lookup(char *name, int create, int value){
	Nameval *sym;
	int h = hash(name);
	for(sym = symtab[h]; sym !=NULL; sym = sym->next)
		if(strcmp(name, sym->name)==0)
			return sym;
	if(create){
		sym = (Nameval *)malloc(sizeof(Nameval));
		sym->name = name;
		sym->value = value;
		sym->next = symtab[h];
		symtab[h] = sym;
	}
	return sym;
}

char* generate_name(int max_length){
	// int len = rand()%max_length+1;
	static int already_added_items = 0;
	int len = max_length;
	char* name = (char*)malloc((len+1)*sizeof(char));
	int i,
		h,
		ch;
	while(1){
		for(i=0; i<len; ++i){
			ch = rand()%(CHARS);
			name[i]=chars[ch];
		}
		h = hash(name);
		if(already_added_items>500){
			if(symtab[h]!=NULL)
				break;
			else
				++generation_complexity;
		}
		else
			break;
	}
	name[i]='\0';
	++already_added_items;
	return name;
}

void print_chains(){
	Nameval* p;
	int occupied = 0;
	int added = 0;
	for(int i = 0; i<NHASH; ++i){
		if(symtab[i]==NULL)
			continue;
		++occupied;
		for(p = symtab[i]; p!=NULL; p=p->next){
			++added;
			printf("<name> %s <value> %d;\t\t\t", p->name, p->value);
		}
		printf("\n");
	}
	printf("\nItems added: %d\n", added);
	printf("Occupied cells: %d\n", occupied);
	printf("Generation complexity: %d\n", generation_complexity);
}

void apply_all(void(*fn)(Nameval*, void *), void *arg){
	Nameval* p;
	for(int i = 0; i<NHASH; ++i){
		if(symtab[i]==NULL)
			continue;
		for(p = symtab[i]; p!=NULL; p = p->next){
			fn(p, arg);
		}
	}
}

void increase_and_print(Nameval *p, void *arg){
	p->value += *(int*)arg;
	printf("%s new value = %d\n",p->name, p->value);
}

int main(void){
	srand((unsigned)time(NULL));
	char* name;
	printf("\n-----MULTIPLIER = %d-----\n\n", MULTIPLIER);
	for(int i = 0; i<MAX_NUM; ++i){
		name = generate_name(MAX_NAME_LEN);
		lookup(name, 1, i);
	}
	print_chains();
	printf("\n\n<apply_all(increase_and_print, (int[]){10000});>\n\n");
	apply_all(increase_and_print, (int[]){10000});
	return 0;
}