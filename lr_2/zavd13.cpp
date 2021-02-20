#include <iostream>
#include <cstring>
using namespace std;

void rev_str(char *str);
void rev_str(char *str1, char *str2);

int main(void){
	char str[] = "test string";
	cout << "Primary line: " << str << endl;
	rev_str(str);
	cout << "Reversed string: " << str << endl;
	int len = strlen(str);
	char another_str[len+1];
	rev_str(str, another_str);
	cout << "Reversed previously reversed string: " << another_str << endl;
	return 0;
}


void rev_str(char* str){
	char temp;
	int len = strlen(str);
	int half_len = len/2;
	for(int i = 0; i < half_len; ++i){
		temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}
}


void rev_str(char *str1, char *str2){
	int len1 = strlen(str1);
	str2[len1] = '\0';
	for(int i = 0; i < len1; ++i){
		str2[len1-i-1] = str1[i]; 
	}
}