#ifndef _TABLE_H
#define _TABLE_H
#include <Windows.h>
#include <CommCtrl.h>
#include <vector>
#include <string>
#include <exception>
#pragma comment(lib,"Comctl32.lib")
using namespace std;

class Table {
private:
	UINT tableOffsetX{};
	HWND hParent{};
	DWORD tableId{};
	vector<vector<wstring>> data {};
	HWND lstView {};
	void InitColumns();
	void InitItems();
	
public:
	Table(HWND parent, DWORD id, UINT tableOffsetX);
	~Table();
	vector<vector<wstring>>& GetData(); //add noexcept
	HWND GetListViewHandle() const;
	LRESULT TableNotify(LPARAM);
	void ResizeTable();
	void CreateTable();
	void UpdateItems();
	void DeleteSelected();
	int GetItemToEdit();
	void ClearData();
};

#endif


