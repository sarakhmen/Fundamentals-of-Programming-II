#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM 100
#define MAX_NAME_LEN 20
#define NHASH 433
#define CHARS 62
const char chars[CHARS] = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

typedef struct Nameval Nameval;
unsigned int hash(char *str, int multiplier);
Nameval* lookup(char *name, int create, int value, int multiplier);
char* generate_name(int max_length);

struct Nameval{
	char *name;
	int value;
	Nameval *next;
};
Nameval *symtab[NHASH];

unsigned int hash(char *str, int multiplier){
	unsigned int h = 0;
	unsigned char *p;
	for(p = (unsigned char *) str; *p != '\0'; p++)
		h = multiplier*h + *p;
	return h % NHASH;
}

Nameval* lookup(char *name, int create, int value, int multiplier){
	Nameval *sym;
	int h = hash(name, multiplier);
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
	int len = rand()%max_length+1;
	// int len = max_length;
	char* name = (char*)malloc((len+1)*sizeof(char));
	int i,
		ch;
	for(i = 0; i<len; ++i){
		ch = rand()%(CHARS);
		name[i]=chars[ch];
	}
	name[i]='\0';
	return name;
}

void print_chains(){
	Nameval* p;
	int occupied = 0;
	int added = 0;
	for(int i = 0; i<NHASH; ++i){
		if(symtab[i]==NULL)
			continue;
		occupied++;
		for(p = symtab[i]; p!=NULL; p=p->next){
			++added;
			printf("<name> %s <value> %d;\t\t\t", p->name, p->value);
		}
		printf("\n");
	}
	printf("\nItems added: %d\n", added);
	printf("Occupied cells: %d", occupied);
}

int main(void){
	srand((unsigned)time(NULL));
	char* name;
	int multiplier = 37;
	for(int i = 0; i<MAX_NUM; ++i){
		name = generate_name(MAX_NAME_LEN);
		lookup(name, 1, i, multiplier);
	}
	print_chains();
	printf("\nMultiplier = %d\n", multiplier);
	return 0;
}