#ifndef _TABLE_H
#define _TABLE_H
#include <Windows.h>
#include <CommCtrl.h>
#include <vector>
#include <string>
#include <exception>
#include "Data.h"
#pragma comment(lib,"Comctl32.lib")
using namespace std;

class Table {
private:
	UINT tableOffsetX{};
	HWND hParent{};
	DWORD tableId{};
	Data* pData{};
	HWND lstView {};
	void InitColumns();
	void InitItems();
	
public:
	Table(HWND parent, DWORD id, Data* data, UINT tableOffsetX);
	~Table();
	HWND GetListViewHandle() const;
	LRESULT TableNotify(LPARAM);
	void ResizeTable();
	void CreateTable();
	void UpdateItems();
	void DeleteSelected();
	int GetItemToEdit();
};

#endif


