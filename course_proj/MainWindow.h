#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include "FileReadWrite.h"
#include "Resource.h"
#include "Table.h"
#include "AddItemDialog.h"
#include "EditItemDialog.h"
#include "FindItemDialog.h"
#include "Data.h"
using namespace std;


class MainWindow : public BaseWindow<MainWindow> {
private:
	Data data{};
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
	void OnButtonReport();
	void FormPeport(const wstring& wcstFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);
	void PipeTableDataToFile(const wstring& wcstFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);
	void ConstructTable(const wstring& wcstBuffer);
public:
	MainWindow();
	~MainWindow();
	PCWSTR ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif