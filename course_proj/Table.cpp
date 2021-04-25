#include "Table.h"


Table::Table(HWND parent, DWORD id){
	CreateTable(parent, id);
	InitColumns();
	InitItems();
}


Table::~Table() {
	CloseHandle(lstView);
}


vector<vector<wstring>>& Table::GetData(){
	return this->data;
}


HWND Table::GetListViewHandle() const {
	return lstView;
}


void Table::ResizeTable(HWND parent) {
	RECT rc;
	GetClientRect(parent, &rc);
	MoveWindow(lstView,
		rc.left + 150,
		rc.top,
		rc.right - rc.left - 150,
		rc.bottom - rc.top,
		TRUE);
}


void Table::CreateTable(HWND parent, DWORD id) {
	INITCOMMONCONTROLSEX icex{};
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);
	lstView = CreateWindow(WC_LISTVIEW,
		L"",
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_OWNERDATA | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		0, 0, 0, 0,
		parent,
		reinterpret_cast<HMENU>(id),
		GetModuleHandle(nullptr),
		NULL);
	if (!lstView)
		throw exception{ "Error while creating ListView" };
	ResizeTable(parent);
}


void Table::InitColumns() {
	LVCOLUMNW lvColumn{};
	wstring szStr[5] = { L"Main Column", L"Column 1", L"Column 2", L"Column 3", L"Column 4" };
	ListView_DeleteAllItems(lstView);
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for (int i = 0; i < 5; i++)
	{
		lvColumn.pszText = &szStr[i][0];
		ListView_InsertColumn(lstView, i, &lvColumn);
	}
}


void Table::InitItems() {
	//data.push_back({ L"1first", L"1second", L"1third", L"1fourth", L"1fifth" });
	//data.push_back({ L"2first", L"2second", L"2third", L"2fourth", L"2fifth" });
	//data.push_back({ L"3first", L"3second", L"3third", L"3fourth", L"3fifth" });
	//data.push_back({ L"4first", L"4second", L"4third", L"4fourth", L"4fifth" });
	//data.push_back({ L"5first", L"5second", L"5third", L"5fourth", L"5fifth" });
	//data.push_back({ L"6first", L"6second", L"6third", L"6fourth", L"6fifth" });
	//data.push_back({ L"7first", L"7second", L"7third", L"7fourth", L"7fifth" });
	//data.push_back({ L"8first", L"8second", L"8third", L"8fourth", L"8fifth" });

	/*LVITEM lvI;
	lvI.pszText = LPSTR_TEXTCALLBACK;
	lvI.mask = LVIF_TEXT | LVIF_STATE;
	lvI.stateMask = 0;
	lvI.iSubItem = 0;
	lvI.state = 0;

	for (int index = 0; index < 8; index++)
	{
		lvI.iItem = index;
		ListView_InsertItem(lstView, &lvI);
	}*/
	UpdateItems();
}


LRESULT Table::TableNotify(LPARAM lParam) {
	LPNMHDR lpnmh = reinterpret_cast<LPNMHDR>(lParam);
	switch (lpnmh->code) {
	case LVN_GETDISPINFO: {
		NMLVDISPINFO* lpdi = reinterpret_cast<NMLVDISPINFO*>(lParam);
		if (lpdi->item.mask & LVIF_TEXT)
			lpdi->item.pszText = &data[lpdi->item.iItem][lpdi->item.iSubItem][0];
		}
		break;

	case LVN_ODCACHEHINT:
		//LPNMLVCACHEHINT   lpCacheHint = (LPNMLVCACHEHINT)lParam;
		//...
		break;

	case LVN_ODFINDITEM:
		//LPNMLVFINDITEM lpFindItem = (LPNMLVFINDITEM)lParam;
		//...
		break;
	}
	return 0;
}


void Table::UpdateItems() {
	ListView_SetItemCount(lstView, data.size());
}