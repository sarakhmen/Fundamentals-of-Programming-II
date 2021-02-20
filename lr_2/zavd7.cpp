#include <cstdlib>
#include <iostream>
using namespace std;

void fn(int a, char **b){
	cout << 1[b-1];
}

int main(int argc, char **argv){
	cout << argv[argc-2] << endl << 6[argv-1] << endl;
	int a = 2;
	char **b = (char**)malloc(2*sizeof(char*));
	b[0] = (char*)calloc(10 , sizeof(char));
	b[1] = (char*)calloc(10 , sizeof(char));
	int i = 0;
	for(i = 0; i < 8; ++i){
		b[0][i] = 'A';
		b[1][i] = 'B';
	}
		b[0][i] = '\0';
		b[1][i] = '\0';
	fn(a, b);
	char arr[4] = "ar";
	cout << 1[arr];
	return EXIT_SUCCESS;
}