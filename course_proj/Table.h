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
	vector<vector<wstring>> data {};
	HWND lstView {};
	void InitColumns();
	void InitItems();
	
public:
	Table(HWND parent, DWORD id);
	~Table();
	vector<vector<wstring>>& GetData(); //add noexcept
	HWND GetListViewHandle() const;
	LRESULT TableNotify(LPARAM);
	void ResizeTable(HWND parent);
	void CreateTable(HWND parent, DWORD id);
	void UpdateItems();
};

#endif