#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM 30
#define MAX_NAME_LEN 10
#define CHARS 62

const char chars[CHARS] = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

typedef struct Nameval Nameval;
typedef struct Hash Hash;

unsigned int hash(int mult, int size, char* str);
Nameval* lookup(Hash* tab, char* name, int create, int value);
char* generate_name(int max_length);
Hash* create_hash_tab();
void delete_hash_tab(Hash* tab);
void print_chains(Hash* tab);
double average_chain_len(Hash* tab);
Hash* rebuild_hash_tab(Hash*);

struct Nameval {
	char* name;
	int value;
	Nameval* next;
};

struct Hash {
	int size;
	int hash_multiplier;
	int tab_multiplier;
	double rebuild_index;
	Nameval** symtab;
};

unsigned int hash(int mult, int size, char* str) {
	unsigned int h = 0;
	unsigned char* p;
	for (p = (unsigned char*)str; *p != '\0'; p++)
		h = mult * h + *p;
	return h % size;
}


Nameval* lookup(Hash* tab, char* name, int create, int value) {
	static int rebuild_counter = 0;
	if (!tab)
		return NULL;
	Nameval* sym;
	unsigned int h = hash(tab->hash_multiplier, tab->size, name);
	for (sym = tab->symtab[h]; sym != NULL; sym = sym->next) {
		if (strcmp(name, sym->name) == 0)
			return sym;
	}
	if (create) {
		sym = (Nameval*)malloc(sizeof(Nameval));
		sym->name = name;
		sym->value = value;
		sym->next = tab->symtab[h];
		tab->symtab[h] = sym;
		if (rebuild_counter >= tab->size / 2) {
			if (tab->rebuild_index <= average_chain_len(tab)) {
				printf("TAB is rebuilding, rebuild_counter = %d, average_chain_len = %.5f\n", rebuild_counter, average_chain_len(tab));
				rebuild_hash_tab(tab);
				printf("TAB WAS REBUILDED, new size = %d\n", tab->size);
				rebuild_counter = 0;
			}
			rebuild_counter -= (int)(0.01 * tab->size);
		}
	}
	++rebuild_counter;
	return sym;

}


char* generate_name(int max_length) {
	// int len = rand()%max_length+1;
	int len = max_length;
	char* name = (char*)malloc((len + 1) * sizeof(char));
	int i,
		key;
	for (i = 0; i < len; ++i) {
		key = rand() % (CHARS);
		name[i] = chars[key];
	}
	name[i] = '\0';
	return name;
}

void print_chains(Hash* tab) {
	if (!tab)
		return;
	Nameval** symtab;
	Nameval* p;
	int occupied = 0;
	int added = 0;
	symtab = tab->symtab;
	for (int i = 0; i < tab->size; ++i) {
		if (symtab[i] == NULL)
			continue;
		++occupied;
		for (p = symtab[i]; p != NULL; p = p->next) {
			++added;
			printf("<name> %s <value> %d;\t", p->name, p->value);
		}
		printf("\n");
	}
	printf("\nItems added: %d\n", added);
	printf("Occupied cells: %d\n", occupied);
}

Hash* create_hash_tab() {
	Hash* tab = (Hash*)malloc(sizeof(Hash));
	if (!tab)
		return NULL;
	tab->symtab = (Nameval**)calloc(1, sizeof(Nameval*));
	if (!tab->symtab)
		tab->size = 0;
	else
		tab->size = 1;
	tab->hash_multiplier = 31;
	tab->tab_multiplier = 2;
	tab->rebuild_index = 1.8;
	return tab;
}

double average_chain_len(Hash* tab) {
	if (!tab || !tab->symtab)
		return -1;
	Nameval* p;
	int chains = 0;
	int len_sum = 0;
	for (int i = 0; i < tab->size; ++i)
		if ((p = tab->symtab[i])) {
			++chains;
			for (; p != NULL; p = p->next)
				++len_sum;
		}
	if (chains == 0)
		return 0;
	else
		return (double)len_sum / chains;

}

Hash* rebuild_hash_tab(Hash* tab) {
	if (!tab)
		return NULL;
	if (!tab->symtab)
		tab->symtab = (Nameval**)calloc(tab->size, sizeof(Nameval*));
	else {
		Nameval** temp = (Nameval**)realloc(tab->symtab, tab->size * tab->tab_multiplier * sizeof(Nameval*));
		if (!temp)
			return tab;
		Nameval* prev,
			* curr;
		int h;
		int size = tab->size;
		int new_size = size * tab->tab_multiplier;
		memset(temp+size, 0, (new_size-size)*sizeof(Nameval*));

		for (int i = 0; i < size; ++i) {
			prev = NULL;

			for (curr = temp[i]; curr != NULL;) {
				h = hash(tab->hash_multiplier, new_size, curr->name);
				if (i != h) {
					if (!prev) {
						temp[i] = curr->next;
						curr->next = temp[h];
						temp[h] = curr;
						curr = temp[i];
					}
					else {
						prev->next = curr->next;
						curr->next = temp[h];
						temp[h] = curr;
						curr = prev->next;
					}
				}
				else {
					prev = curr;
					curr = curr->next;
				}
			}
		}
		tab->symtab = temp;
		tab->size = new_size;
	}

	return tab;
}


void delete_hash_tab(Hash *tab) {
	if (!tab)
		return;
	if (tab->symtab) {
		Nameval *curr,
				*next;
		for (int i = 0; i < tab->size; ++i)
			for (curr = tab->symtab[i]; curr != NULL; curr = next){
				next = curr->next;
				free(curr->name);
				free(curr);
			}
		free(tab->symtab);
	}
	free(tab);
}


int main(void) {
	Hash* tab = create_hash_tab();
	srand((unsigned)time(NULL));
	char* name;
	printf("\n-----MULTIPLIER = %d-----\n\n", tab->hash_multiplier);
	for (int i = 0; i < MAX_NUM; ++i) {
		name = generate_name(MAX_NAME_LEN);
		lookup(tab, name, 1, i);
	}
	printf("\n\n<Hash tab contents>\n\n");
	print_chains(tab);
	delete_hash_tab(tab);
	printf("\n\n");
	return 0;
}