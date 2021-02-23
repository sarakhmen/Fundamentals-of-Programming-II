#include <iostream>
#include <cstring>

using namespace std;

#define SIZE 255

class strtype{
	char *p;
	int len;
public:
	strtype();
	strtype(const char* str);
	~strtype();
	void set(char const *ptr);
	void show();		
};

strtype::strtype(){
	p = new char[SIZE];
	if(!p){
		cout << "Allocation error.\n";
		exit(1);
	}
	*p = '\0';
	len = 0;
}

strtype::strtype(const char* str){
	p = new char[SIZE];
	if(!p){
		cout << "Allocation error.\n";
		exit(1);
	}
	if(strlen(str) > SIZE){
		cout << "String too big\n";
		*p = '\0';
		len = 0;
		return;
	}
	strcpy(p, str);
	len = strlen(p);
}


strtype::~strtype(){
	cout << "Freeing p\n";
	delete[] p;
}

void strtype::set(char const *ptr){
	if(strlen(ptr) > SIZE){
		cout << "String too big\n";
		return;
	}
	strcpy(p, ptr);
	len = strlen(p);
}

void strtype::show(){
	cout << p << "-length : " << len;
	cout << "\n";
}

int main(){
	strtype s1("This is a test."), 
			s2{};
	s2.set("I like C++.");
	s1.show();
	s2.show();
	return 0;
}

