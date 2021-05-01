#ifndef _H_ADD_ITEM_DIALOG
#define _H_ADD_ITEM_DIALOG

#include <Windows.h>
#include <vector>
#include <string>
#include "BaseWindow.h"
#include "FileReadWrite.h"
#include "Resource.h"
#include "Data.h"
using namespace std;

class AddItemDialog : public BaseWindow<AddItemDialog> {
private:
	bool endLoop{};
	HWND parent{};
	Data* pData{};
	void OnCreate();
	void MessageLoop();
	HWND CreateEditTextControl(DWORD id, int X, int Y, int nWidth, int nHeight, int textLength);
	HWND CreateStaticTextControl(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight);
	void CleanEditTextFields();
	void OnButtonAdd();
public:
	AddItemDialog(HWND, Data*);
	~AddItemDialog();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void GetUserInput();
};

#endif

