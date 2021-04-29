#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
#include "BaseWindow.h"
#include "FileReadWrite.h"
#include "Resource.h"
#include "Table.h"
#include "AddItemDialog.h"
#include "EditItemDialog.h"
#include "FindItemDialog.h"
#pragma comment(lib,"Comctl32.lib")
using namespace std;


class MainWindow : public BaseWindow<MainWindow> {
private:
	EditItemDialog* editItemDialog {};
	AddItemDialog* addItemDialog {};
	FindItemDialog* findItemDialog{};
	Table* pTable {};
	BOOL CreateButtons();
	void OnButtonClicked(WPARAM wParam, LPARAM lParam);
	void OnCreate();
	void OnDeleteSelected();
	void OnButtonAddItem();
	void OnButtonEditItem();
	void OnButtonClear();
	void OnButtonLoadData();
	void OnButtonSaveData();
	void OnButtonFindItem();
	void PipeTableDataToFile(const wstring& wcstFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);
	void ConstructTable(const wstring& wcstBuffer);
public:
	MainWindow();
	~MainWindow();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif