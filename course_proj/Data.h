#ifndef _H_DATA
#define _H_DATA

#include <vector>
#include <string>
using namespace std;

class Data {
	vector<vector<wstring>> vecData{};
	vector<int> indexMask{};
	bool bMask{ false };
public:
	Data() {}
	void pushBack(const vector<wstring>& elem);
	vector<vector<wstring>>::iterator erase(int iPos);
	vector<wstring>& operator[](int iPos);
	void clear();
	bool isMask();
	size_t relative_size();
	size_t real_size();
	void setMask(bool);
	void pushMaskIndex(int);
};

#endif