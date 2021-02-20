#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 20

typedef struct Tree Tree;

Tree *add_to_tree(Tree *root, int new_value);
void tree_to_array(Tree *root, int arr[]);
void sort_tree(int arr[], int elem_total);

struct Tree {
	int data;
	Tree *left;
	Tree *right;
};

Tree *add_to_tree(Tree *root, int new_value)
{
	if (root==NULL)
    	{
        	root = (Tree*)malloc(sizeof(Tree));
        	root->data = new_value;
        	root->left = root->right = NULL;
        	return root;
     	}
   	if (root->data < new_value)
     	root->right = add_to_tree(root->right, new_value);
   	else
     	root->left  = add_to_tree(root->left,  new_value);
   	return root;
}
 
void tree_to_array(Tree *root, int arr[])
{
	static int max=0; 
    if (root==NULL) 
    	return; 
    tree_to_array(root->left, arr);
    arr[max++] = root->data;
    tree_to_array(root->right, arr); 
}
 
void sort_tree(int arr[], int elem_total) 
{
   	Tree *root = NULL;
   	for(int i=0; i<elem_total; ++i)
    	root = add_to_tree(root, arr[i]);
   	tree_to_array(root, arr);
}


int main(void){
	srand((unsigned)time(NULL));
	int arr[MAX_SIZE];
	for(int i = 0; i<MAX_SIZE; ++i)
		arr[i] = rand();
	sort_tree(arr, MAX_SIZE);
	printf("Sorted array:\n");
	for(int i = 0; i<MAX_SIZE; ++i) 
		printf("%d ", arr[i]); 
	return 0;
}