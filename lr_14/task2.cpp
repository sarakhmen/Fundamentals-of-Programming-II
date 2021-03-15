#include <iostream>
#include <cstring>
using namespace std;

class strtype
{
	char str[80];
	int len;

public:
	strtype(const char *s)
	{
		strcpy(str, s);
		len = strlen(s);
	}
	operator char *() { return str; }
	operator int(){ return strlen(str);}
};

int main()
{
	strtype s("This is a test");
	char *p, s2[80];
	p = s;
	cout << "Here is string: " << p << '\n';
	strcpy(s2, s);
	cout << "Here is copy of string: " << s2 << '\n';
    int len = s;
	cout << "Here is string converted to int: " << len << '\n';
	return 0;
}