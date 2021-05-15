#include "stdafx.h"
#include "EditItemDialog.h"

EditItemDialog::EditItemDialog(HWND hwndParent, Data* pData) {
	parent = hwndParent;
	this->pData = pData;
}


EditItemDialog::~EditItemDialog() {
	if (m_hwnd)
		CloseHandle(m_hwnd);
}


PCWSTR EditItemDialog::ClassName() const {
	return L"Edit item dialog";
}


LRESULT EditItemDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		OnCreate();
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_EDITITEMDIALOG_BUTTON_EDIT:
			OnButtonEdit();
			break;
		}
		return 0;

	case WM_CLOSE:
		endLoop = true;
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


void EditItemDialog::GetUserEdit(int iItem) {
	iItemToEdit = iItem;
	EnableWindow(parent, FALSE);
	ShowWindow(m_hwnd, SW_SHOW);
	InitializeContent(iItem);
	MessageLoop();
	EnableWindow(parent, TRUE);
	ShowWindow(m_hwnd, SW_HIDE);
	SetFocus(parent);
}


void EditItemDialog::MessageLoop() {
	MSG msg{};
	endLoop = false;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (endLoop == true) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	PrintConsole(L"returned\n");
}


void EditItemDialog::OnCreate() {
	//check if creation is successful
	wstring labels[TABLE_COL_NUMBER] = { TEXT_LABEL_0, TEXT_LABEL_1, TEXT_LABEL_2,  TEXT_LABEL_3, TEXT_LABEL_4 };
	for (int i = 0; i < TABLE_COL_NUMBER; ++i) {
		CreateEditTextControl(IDC_ITEMDIALOG_EDIT_0 + i, 110, 15 + i * 45, 260, 30, MAX_STR_LEN_COL[i]);
		CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT_0 + i, labels[i].c_str(), 10, 15 + i * 45, 100, 30);
	}

	CreateWindow(L"BUTTON", L"Редагувати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		130, 250, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_EDITITEMDIALOG_BUTTON_EDIT),
		GetModuleHandle(nullptr), nullptr);
	EnumChildWindows(m_hwnd, [](HWND child, LPARAM font) {
		SendMessage(child, WM_SETFONT, font, true);
		return TRUE;
		}, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
}


HWND EditItemDialog::CreateEditTextControl(DWORD id, int X, int Y, int nWidth, int nHeight, int textLength) {
	HWND hEdit = CreateWindowExW(
		WS_EX_CLIENTEDGE, L"EDIT",
		nullptr,
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL |
		ES_LEFT | WS_BORDER,
		X, Y, nWidth, nHeight,
		m_hwnd,
		reinterpret_cast<HMENU>(id),
		GetModuleHandle(nullptr),
		nullptr);
	SendMessage(hEdit, EM_SETLIMITTEXT, textLength, 0);

	return hEdit;
}


HWND EditItemDialog::CreateStaticTextControl(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight) {
	HWND hStatic = CreateWindow(
		L"STATIC",
		szStr,
		WS_VISIBLE | WS_CHILD | SS_LEFT,
		X,
		Y,
		nWidth,
		nHeight,
		m_hwnd,
		reinterpret_cast<HMENU>(id),
		GetModuleHandle(0),
		nullptr);

	return hStatic;
}


void EditItemDialog::CleanEditTextFields() {
	for (int i = 0; i < TABLE_COL_NUMBER; ++i) {
		SetWindowText(GetDlgItem(m_hwnd, IDC_ITEMDIALOG_EDIT_0 + i), L"");
	}
}


void EditItemDialog::OnButtonEdit() {
	wstring wstr[TABLE_COL_NUMBER]{};
	for (int i = 0; i < TABLE_COL_NUMBER; ++i) {
		wstr[i].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_ITEMDIALOG_EDIT_0 + i)));
		GetWindowText(GetDlgItem(m_hwnd, IDC_ITEMDIALOG_EDIT_0 + i), &wstr[i][0], wstr[i].size() + 1);
	}
	for (int i = 0; i < TABLE_COL_NUMBER; ++i)
		if (wstr[i] == L"") {
			MessageBox(m_hwnd, L"Всі поля повинні бути заповнені", L"Попередження", MB_OK | MB_ICONWARNING);
			return;
		}

	vector<wstring> temp;
	for (int i = 0; i < TABLE_COL_NUMBER; ++i)
		temp.push_back(wstr[i]);
	(*pData)[iItemToEdit] = temp;
	MessageBox(m_hwnd, L"Об'єкт успішно змінено!", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	endLoop = true;
	//CleanEditTextFields();
}


void EditItemDialog::InitializeContent(int iItem) {
	for (int i = 0; i < TABLE_COL_NUMBER; ++i)
		SetWindowText(GetDlgItem(m_hwnd, IDC_ITEMDIALOG_EDIT_0 + i), (*pData)[iItem][i].c_str());
}