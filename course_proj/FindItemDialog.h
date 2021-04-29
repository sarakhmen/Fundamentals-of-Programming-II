#ifndef _H_FIND_ITEM_DIALOG
#define _H_FIND_ITEM_DIALOG

#include <Windows.h>
#include <vector>
#include <string>
#include "BaseWindow.h"
#include "FileReadWrite.h"
#include "Resource.h"
using namespace std;

class FindItemDialog : public BaseWindow<FindItemDialog> {
private:
	bool endLoop{};
	HWND parent{};
	vector<vector<wstring>>* pData{};
	void OnCreate();
	void MessageLoop();
	HWND CreateFindItemButton(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight);
	void OnButtonFind(DWORD id, int maxTextLength, int iColumn);

public:
	FindItemDialog(HWND, vector<vector<wstring>>*);
	~FindItemDialog();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void GetUserFind();
};

#endif