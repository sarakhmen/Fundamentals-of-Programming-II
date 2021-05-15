#ifndef _H_FIND_ITEM_DIALOG
#define _H_FIND_ITEM_DIALOG

#include "FileReadWrite.h"
#include "Resource.h"
#include "Data.h"
using namespace std;

class FindItemDialog : public BaseWindow<FindItemDialog> {
private:
	bool endLoop{};
	HWND parent{};
	Data* pData{};
	void OnCreate();
	void MessageLoop();
	HWND CreateFindItemButton(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight);
	void OnButtonFind(DWORD id, int maxTextLength, int iColumn);

public:
	FindItemDialog(HWND, Data*);
	~FindItemDialog();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void GetUserFind();
};

#endif