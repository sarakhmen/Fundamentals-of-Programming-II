#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(a, b) ((a >= b)? a : b)
typedef struct Nameval Nameval;
typedef struct Tree Tree;

Nameval *lookup(Nameval *treep, char *name);
Nameval *insert(Nameval *treep, Nameval *newp);
Nameval *nrlookup(Nameval *treep, char *name);
Tree *insert_into_tree(Tree *treep, int data);
int is_balanced(Tree* root);


struct Nameval {
	char *name;
	int value;
	Nameval *left;
	Nameval *right;
};

struct Tree {
	int data;
	Tree *left;
	Tree *right;
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

int is_balanced(Tree* root){
	if(root == NULL)
		return 0;
	int l_height = 1 + is_balanced(root->left);
	int r_height = 1 + is_balanced(root->right);
	if(l_height == 0 || r_height == 0 || abs(l_height - r_height) > 1)
		return -1;
	return MAX(l_height, r_height);
}

Tree *insert_into_tree(Tree *treep, int data){
	if(treep == NULL){
		Tree *p = (Tree*)malloc(sizeof(Tree));
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	int cmp = treep->data - data;
	if(cmp == 0)
		printf("insert: duplicate entry %d ignored\n", data);
	else if(cmp > 0)
		treep->left = insert_into_tree(treep->left, data);
	else 
		treep->right = insert_into_tree(treep->right, data);
	return treep;
}

void print_tree(Tree *treep){
	if(treep == NULL)
		return;
	print_tree(treep->left);
	printf("%d  ", treep->data);
	print_tree(treep->right);
	
}

int main(void){
	Tree *treep1 = NULL;
	treep1 = insert_into_tree(treep1, 5);
	srand((unsigned)time(NULL));
	printf("Generating tree with the random input...\n");
	for(int i = 0; i<10; ++i)
		insert_into_tree(treep1, rand()%11);
	int balanced = is_balanced(treep1);
	if(balanced!=-1)
		printf("The tree with the random input is balanced! The length of the longest path is %d\n", balanced-1);
	else
		printf("The tree with the random input is not balanced((9\n");
	Tree *treep2 = NULL;
	printf("Generating tree with the sort input...\n");
	for(int i = 0; i<10; ++i)
		treep2 = insert_into_tree(treep2, i);
	balanced = is_balanced(treep2);
	if(balanced == -1)
		printf("The tree with the sort input is not balanced!");
	else
		printf("The tree with the sort input is balanced((9\n");
	return 0;
}