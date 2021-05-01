#include "Table.h"


Table::Table(HWND parent, DWORD id, Data* data, UINT tableOffsetX){
	hParent = parent;
	tableId = id;
	pData = data;
	this->tableOffsetX = tableOffsetX;
	CreateTable();
	InitColumns();
	InitItems();
}


Table::~Table() {
	CloseHandle(lstView);
}


HWND Table::GetListViewHandle() const {
	return lstView;
}


void Table::ResizeTable() {
	RECT rc;
	GetClientRect(hParent, &rc);
	MoveWindow(lstView,
		rc.left + tableOffsetX,
		rc.top,
		rc.right - rc.left - tableOffsetX,
		rc.bottom - rc.top,
		TRUE);
}


void Table::CreateTable() {
	INITCOMMONCONTROLSEX icex{};
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);
	lstView = CreateWindow(WC_LISTVIEW,
		L"",
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_OWNERDATA | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
		0, 0, 0, 0,
		hParent,
		reinterpret_cast<HMENU>(tableId),
		GetModuleHandle(nullptr),
		NULL);
	if (!lstView)
		throw exception{ "Error while creating ListView" };
	ListView_SetExtendedListViewStyle(lstView, LVS_EX_FULLROWSELECT);
	ResizeTable();
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
	pData->pushBack({ L"1first", L"1second", L"1third", L"1fourth", L"1fifth" });
	pData->pushBack({ L"2first", L"2second", L"2third", L"2fourth", L"2fifth" });
	pData->pushBack({ L"3first", L"3second", L"3third", L"3fourth", L"3fifth" });
	pData->pushBack({ L"4first", L"4second", L"4third", L"4fourth", L"4fifth" });
	pData->pushBack({ L"5first", L"5second", L"5third", L"5fourth", L"5fifth" });
	pData->pushBack({ L"6first", L"6second", L"6third", L"6fourth", L"6fifth" });
	pData->pushBack({ L"7first", L"7second", L"7third", L"7fourth", L"7fifth" });
	pData->pushBack({ L"8first", L"8second", L"8third", L"8fourth", L"8fifth" });

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
			lpdi->item.pszText = &(*pData)[lpdi->item.iItem][lpdi->item.iSubItem][0];
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
	ListView_SetItemCount(lstView, pData->size());
}


void Table::DeleteSelected() {
	int iPos = ListView_GetNextItem(lstView, -1, LVNI_SELECTED);
	if (iPos == -1)
		MessageBox(hParent, L"Жоден елемент не виділено", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	else if (MessageBox(hParent, L"Ви дійсно хочете видалити всі виділені елементи?", L"Підтвердження видалення", MB_OKCANCEL) == IDOK) {
		vector<int> iVec;
		while (iPos != -1) {
			iVec.push_back(iPos);
			iPos = ListView_GetNextItem(lstView, iPos , LVNI_SELECTED);
		}
		for(size_t i = 0; i < iVec.size(); ++i)
			pData->erase(iVec[i] - i);
		ListView_SetItemCount(lstView, pData->size());
		MessageBox(hParent, L"Елементи успішно видалено", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
}


int Table::GetItemToEdit() {
	int iPos = ListView_GetNextItem(lstView, -1, LVNI_SELECTED);
	if(iPos != -1) {
		if (ListView_GetNextItem(lstView, iPos, LVNI_SELECTED) != -1) {
			MessageBox(hParent, L"Виділено забагато елементів, виберіть лише один", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
			iPos = -1;
		}
	}
	else {
		MessageBox(hParent, L"Виділіть один елемент, який потрібно редагувати", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
	return iPos;
}
