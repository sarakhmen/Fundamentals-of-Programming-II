#include "stdafx.h"
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
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_OWNERDATA | WS_VISIBLE | WS_TABSTOP,
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
	wstring szStr[TABLE_COL_NUMBER] = { COL_NAME_0, COL_NAME_1, COL_NAME_2, COL_NAME_3, COL_NAME_4};
	ListView_DeleteAllItems(lstView);
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for (int i = 0; i < TABLE_COL_NUMBER; i++)
	{
		if (i == 0)
			lvColumn.cx = 55;
		else if (i == 1)
			lvColumn.cx = 120;
		else if (i == 2)
			lvColumn.cx = 200;
		else
			lvColumn.cx = 100;
		lvColumn.pszText = &szStr[i][0];
		ListView_InsertColumn(lstView, i, &lvColumn);
	}
}

	
void Table::InitItems() {
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Власюк Іван Вікторович", L"(unknown)", L"+380961921937" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Гончарова Єлизавета Максимівна", L"(unknown)", L"+380683875850" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Груздов Максим Олексійович", L"(unknown)", L"+380958067355" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Дудкін Олексій Миколайович", L"(unknown)", L"+380663609313" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Занченко Олексій Дмитрович", L"(unknown)", L"+380916011975" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Захарчук Євгеній Миколайович", L"(unknown)", L"+380970807396" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Котова Анна Андріївна", L"(unknown)", L"+380683875850" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Кравченко Дарія Олександрівна", L"(unknown)", L"+380500110070" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Кубрак Сергій Володимирович", L"(unknown)", L"+380961893911" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Кушнірук Тетяна Олександрівна", L"(unknown)", L"+380969874634" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Лагойда Михайло Мирославович", L"(unknown)", L"+380990929832" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Луговий Святослав Богданович", L"(unknown)", L"+380673973248" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Мангуплі Юлія Дмитрівна", L"(unknown)", L"+380995067428" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Марченко Кіріл Андрійович", L"(unknown)", L"+380672002145" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Міньков Іван Вікторович", L"(unknown)", L"+380999761234" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Мітлицький Владислав Віталійович", L"(unknown)", L"+380964058502" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Моругий Олег Петрович", L"(unknown)", L"+380739963137" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Мосолов Максим Олегович", L"(unknown)", L"+380997974831" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Сарахман Артур Олегович", L"(unknown)", L"+380971266262" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Сідорська Анна Володимирівна", L"(unknown)", L"+380935482623" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Сокирка Кирило Вікторович", L"(unknown)", L"+380665233927" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Сугулов Єгор Сергійович", L"(unknown)", L"+380963268933" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Філюк Дмитро Віталійович", L"(unknown)", L"+380678695532" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Чуй Богдан Сергійович", L"(unknown)", L"+380633129707" });
	pData->pushBack({ L"ТІ-02", L"(unknown)", L"Чукін Сергій Віталійович", L"(unknown)", L"+380932019309" });
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
	ListView_SetItemCount(lstView, pData->relative_size());
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
		ListView_SetItemCount(lstView, pData->relative_size());
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
