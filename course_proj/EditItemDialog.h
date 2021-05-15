#ifndef _H_EDIT_ITEM_DIALOG
#define _H_EDIT_ITEM_DIALOG
#include "FileReadWrite.h"
#include "Resource.h"
#include "Data.h"
using namespace std;

class EditItemDialog : public BaseWindow<EditItemDialog> {
private:
	int iItemToEdit{};
	bool endLoop{};
	HWND parent{};
	Data* pData{};
	void OnCreate();
	void MessageLoop();
	HWND CreateEditTextControl(DWORD id, int X, int Y, int nWidth, int nHeight, int textLength);
	HWND CreateStaticTextControl(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight);
	void CleanEditTextFields();
	void OnButtonEdit();
	void InitializeContent(int);

public:
	EditItemDialog(HWND, Data*);
	~EditItemDialog();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void GetUserEdit(int);
};

#endif