#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tree Tree;

Tree *lookup(Tree *treep, int data);
Tree *nrlookup(Tree *treep, int data);
Tree *insert_into_tree(Tree *treep, int data);
void delete_tree(Tree *);

struct Tree {
	int data;
	Tree *left;
	Tree *right;
};

Tree *lookup(Tree *treep, int data){
	if(treep == NULL)
		return NULL;
	int cmp = treep->data - data;
	if(cmp == 0)
		return treep;
	else if (cmp > 0)
		return lookup(treep->left, data);
	else 
		return lookup(treep->right, data);
}

Tree *nrlookup(Tree *treep, int data){
	while(treep != NULL){
		int cmp = treep->data - data;
		if(cmp == 0)
			return treep;
		else if (cmp > 0)
			treep = treep->left;
		else
			treep = treep->right;
	}
	return NULL;
}


Tree *insert_into_tree(Tree *treep, int data){
	if(treep == NULL){
		treep = (Tree*)malloc(sizeof(Tree));
		treep->data = data;	
		treep->left = NULL;
		treep->right = NULL;
		return treep;
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

void delete_tree(Tree *treep){
	if(treep == NULL)
		return;
	delete_tree(treep->left);
	delete_tree(treep->right);
	free(treep);
}

int main(void){
	
	Tree *treep = NULL;
	for(int i = 0; i<30000; ++i)
		treep = insert_into_tree(treep, i);
	clock_t begin = clock();
	Tree *found = lookup(treep, 29999);
	clock_t end = clock();
	printf("The lookup function lasted for %.3f seconds\n", (double)(end-begin)/CLOCKS_PER_SEC);
	begin = clock();
	found = nrlookup(treep, 29999);
	end = clock();
	printf("The nrlookup function lasted for %.3f seconds\n", (double)(end-begin)/CLOCKS_PER_SEC);
	delete_tree(treep);

	return 0;
}