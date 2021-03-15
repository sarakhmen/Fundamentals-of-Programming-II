#include <iostream>
#include <cstring>
using namespace std;
class output
{
	static char outbuf[255];
	static int inuse;
	static int oindex;
	char str[80];
	int i;
	int who;
public:
	output(int w, const char *s)
	{
		strcpy(str, s);
		i = 0;
		who = w;
	}
	int putbuf()
	{
		if (!str[i])
		{			   
			inuse = 0; 
			return 0;
		}
		if (!inuse){
			inuse = who;
		}
		if (inuse != who){
			cout << "object " << who << " doesn't have a permission" << endl;
			return -1;
		}
		if (str[i])
		{
			cout << "used by object " << who << endl;
			outbuf[oindex] = str[i];
			i++;
			oindex++;
			outbuf[oindex] = '\0';
			return 1;
		}
		return 0;
	}
	void show() { cout << outbuf << '\n'; }
};
char output::outbuf[255];
int output::inuse = 0;
int output::oindex = 0;
int main()
{
	output obj1(1, "This is a test "), obj2(2, "of statics");
	while (obj1.putbuf() | obj2.putbuf());
	obj1.show();
	return 0;
}