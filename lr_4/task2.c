#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum{
	NPREF = 2,
	NHASH = 5,
    MULTIPLIER=31,
    NHASH2 = 2000,
	MAXGEN = 10000
};

typedef struct State State;
typedef struct Suffix Suffix;
typedef struct List List;


struct List{
    char *word;
    List *next;
};

struct State {
	char *pref[NPREF];
	Suffix *suf;
	State *next;
};

struct Suffix{
	char *word;
	Suffix *next;
};

State *statetab[NHASH];
List *wordtab[NHASH2];
char NONWORD[] = "\n";



State *lookup(char *prefix[NPREF], int create);
char *add_to_tab(char *word);
unsigned int hash(char *s[NPREF]);
unsigned int hash2(char *w);
void build( char *prefix [NPREF], FILE *f);
void addsuffix(State *sp, char *suffix);
void add(char *prefix[NPREF], char *suffix);
void generate(int nwords);



int main(void){
	clock_t begin = clock();
	int nwords = MAXGEN;
	char *prefix[NPREF];
	for(int i=0; i<NPREF; i++){
		prefix[i] = NONWORD;
	}
	
	FILE *file;
	file = fopen("large_text.txt", "r");
	if(file){
		build(prefix, file);
		fclose(file);
	}
	add(prefix, NONWORD);
	generate(nwords);
	printf("Elapsed time = %fs", (double)(clock() - begin)/CLOCKS_PER_SEC);
	return 0;
}



State *lookup(char *prefix[NPREF], int create){
	int i;
	State *sp;
	int h = hash(prefix);
	for(sp = statetab[h]; sp != NULL; sp = sp->next){
		for(i = 0; i < NPREF; i++)
			if(prefix[i] != sp->pref[i])
				break;
		if(i == NPREF)
			return sp;
	}
	if(create){
		sp = (State *)malloc(sizeof(State));
		if(sp == NULL){
			perror("Memory allocation error.\n");
			exit(1);
		}
		for(i = 0; i < NPREF; i++){
			sp->pref[i]=prefix[i];
		}
		sp->suf = NULL;
		sp->next = statetab[h];
		statetab[h] = sp;
	}
	return sp;
}


unsigned int hash(char *s[NPREF]){
	unsigned int h = 0;
	unsigned char *p;
	for(int i = 0; i < NPREF; i++){
		for(p = (unsigned char *)s[i]; *p != '\0'; p++){
			h = MULTIPLIER*h + *p;
		}
	}
	return h % NHASH;
}


void build( char *prefix [NPREF], FILE *f){
	char buf[1000], fmt[100];
	sprintf(fmt, "%%%lds", sizeof(buf)-1);
	printf("fmt=\"%s\"\n", fmt);
	while(fscanf(f, fmt, buf) != EOF){
		printf("%s ", buf);
		add(prefix, add_to_tab(buf));
	}
	putchar('\n');
}

void addsuffix(State *sp, char *suffix){
	Suffix *suf;
	suf = (Suffix *)malloc(sizeof(Suffix));
	if(suf == NULL){
		perror("Memory allocation error.\n");
		exit(1);
	}
	suf->word = suffix;
	suf->next = sp->suf;
	sp->suf = suf;
}

void add(char *prefix[NPREF], char *suffix){
	State *sp;
	sp = lookup(prefix, 1);
	addsuffix(sp, suffix);
	memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
	prefix[NPREF-1] = suffix;
}

void generate(int nwords){
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, nmatch;
	for( i = 0; i<NPREF; i++){
		prefix[i] = NONWORD;
	}
	for(i=0; i<nwords; i++){
		sp = lookup(prefix, 0);
		nmatch = 0;
		for(suf = sp->suf; suf != NULL; suf = suf->next){
			if(rand() % ++nmatch == 0){
				w = suf->word;
			}
		}
		if(w == NONWORD)
			break;
		// printf("%s\n", w);
		memmove(prefix, prefix+1, (NPREF-1) * sizeof(prefix[0]));
		prefix[NPREF-1] = w;
	}
}


char *add_to_tab(char *word){
    List *ls;
    unsigned h = hash2(word);
    for(ls = wordtab[h]; ls!=NULL; ls = ls->next){
        if(strcmp(word, ls->word) == 0)
            return ls->word;
    }
    List *node = (List*)malloc(sizeof(List));
	char *t = (char *)malloc(strlen(word)+1);
	if(!node || !t){
        printf("Memory allocation error.\n");
        exit(1);
    }
	strcpy(t, word);
	node->word = t;
    node->next = wordtab[h];
    wordtab[h] = node;
    return t;
}

unsigned int hash2(char *w){
	unsigned int h = 0;
	unsigned char *p;
	for(p = (unsigned char *) w; *p != '\0'; p++)
		h = MULTIPLIER*h + *p;
	return h % NHASH2;
}