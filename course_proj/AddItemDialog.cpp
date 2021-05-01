#include "AddItemDialog.h"


AddItemDialog::AddItemDialog(HWND hwndParent, Data* pData) {
	parent = hwndParent;
	this->pData = pData;
}


AddItemDialog::~AddItemDialog() {
	if(m_hwnd)
		CloseHandle(m_hwnd);
}


PCWSTR AddItemDialog::ClassName() const {
	return L"Add item dialog";
}


LRESULT AddItemDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		OnCreate();
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_ADDITEMDIALOG_BUTTON_ADD:
			OnButtonAdd();
			break;
		}
		return 0;

	case WM_CLOSE:
		CleanEditTextFields();
		endLoop = true;
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


void AddItemDialog::GetUserInput() {
	EnableWindow(parent, FALSE);
	ShowWindow(m_hwnd, SW_SHOW);
	MessageLoop();
	EnableWindow(parent, TRUE);
	ShowWindow(m_hwnd, SW_HIDE);
	SetFocus(parent);
}


void AddItemDialog::MessageLoop() {
	MSG msg{};
	endLoop = false;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (endLoop == true) {
			PrintConsole(L"must be closed\n");
			break;
		}
		/*PrintConsole(L"AddItem sms received\n");*/
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	PrintConsole(L"returned\n");
}


void AddItemDialog::OnCreate() {
	PrintConsole(L"ON_CREATE\n");
	//check if creation is successful
	CreateEditTextControl(IDC_EDIT1, 200, 15, 260, 30, MAX_STR_LEN_COL1);
	CreateEditTextControl(IDC_EDIT2, 200, 60, 260, 30, MAX_STR_LEN_COL2);
	CreateEditTextControl(IDC_EDIT3, 200, 105, 260, 30, MAX_STR_LEN_COL3);
	CreateEditTextControl(IDC_EDIT4, 200, 150, 260, 30, MAX_STR_LEN_COL4);
	CreateEditTextControl(IDC_EDIT5, 200, 195, 260, 30, MAX_STR_LEN_COL5);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT1, L"Поле №1", 10, 20, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT2, L"Поле №2", 10, 65, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT3, L"Поле №3", 10, 110, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT4, L"Поле №4", 10, 155, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT5, L"Поле №5", 10, 200, 150, 30);
	CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		180, 250, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_ADDITEMDIALOG_BUTTON_ADD),
		GetModuleHandle(nullptr), nullptr);
}


HWND AddItemDialog::CreateEditTextControl(DWORD id, int X, int Y, int nWidth, int nHeight, int textLength) {
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


HWND AddItemDialog::CreateStaticTextControl(DWORD id, LPCWSTR szStr,int X, int Y, int nWidth, int nHeight) {
	HWND hStatic = CreateWindow(
		L"STATIC",
		szStr,
		WS_VISIBLE | WS_CHILD | SS_CENTER,
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


void AddItemDialog::CleanEditTextFields() {
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT1), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT2), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT3), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT4), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT5), L"");
}


void AddItemDialog::OnButtonAdd() {
	wstring wstr[5]{};
	wstr[0].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_EDIT1)));
	GetWindowText(GetDlgItem(m_hwnd, IDC_EDIT1), &wstr[0][0], wstr[0].size() + 1);
	wstr[1].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_EDIT2)));
	GetWindowText(GetDlgItem(m_hwnd, IDC_EDIT2), &wstr[1][0], wstr[1].size() + 1);
	wstr[2].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_EDIT3)));
	GetWindowText(GetDlgItem(m_hwnd, IDC_EDIT3), &wstr[2][0], wstr[2].size() + 1);
	wstr[3].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_EDIT4)));
	GetWindowText(GetDlgItem(m_hwnd, IDC_EDIT4), &wstr[3][0], wstr[3].size() + 1);
	wstr[4].resize(GetWindowTextLength(GetDlgItem(m_hwnd, IDC_EDIT5)));
	GetWindowText(GetDlgItem(m_hwnd, IDC_EDIT5), &wstr[4][0], wstr[4].size() + 1);
	
	if (wstr[0] == L"" || wstr[1] == L"" || wstr[2] == L"" || wstr[3] == L"" || wstr[4] == L"") {
		MessageBox(m_hwnd, L"Всі поля повинні бути заповнені", L"Попередження", MB_OK | MB_ICONWARNING);
		return;
	}

	pData->pushBack({ wstr[0], wstr[1], wstr[2], wstr[3], wstr[4] });
	MessageBox(m_hwnd, L"Об'єкт успішно додано до таблиці!", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	CleanEditTextFields();
}