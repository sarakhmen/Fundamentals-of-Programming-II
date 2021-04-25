#include "EditItemDialog.h"

EditItemDialog::EditItemDialog(HWND hwndParent, vector<vector<wstring>>* pData) {
	parent = hwndParent;
	this->pData = pData;
}


EditItemDialog::~EditItemDialog() {
	if (Window())
		CloseHandle(Window());
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


void EditItemDialog::GetUserInput() {
	EnableWindow(parent, FALSE);
	ShowWindow(Window(), SW_SHOW);
	MessageLoop();
	EnableWindow(parent, TRUE);
	ShowWindow(Window(), SW_HIDE);
	SetFocus(parent);
}


void EditItemDialog::MessageLoop() {
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


void EditItemDialog::OnCreate() {
	PrintConsole(L"ON_CREATE\n");
	//check if creation is successful
	CreateEditTextControl(ID_ADDITEMDIALOG_EDIT1, 200, 15, 260, 30, EDITTEXT1_MAX_LENGTH);
	CreateEditTextControl(ID_ADDITEMDIALOG_EDIT2, 200, 60, 260, 30, EDITTEXT2_MAX_LENGTH);
	CreateEditTextControl(ID_ADDITEMDIALOG_EDIT3, 200, 105, 260, 30, EDITTEXT3_MAX_LENGTH);
	CreateEditTextControl(ID_ADDITEMDIALOG_EDIT4, 200, 150, 260, 30, EDITTEXT4_MAX_LENGTH);
	CreateEditTextControl(ID_ADDITEMDIALOG_EDIT5, 200, 195, 260, 30, EDITTEXT5_MAX_LENGTH);
	CreateStaticTextControl(IDC_ADDITEMDIALOG_STATIC_TEXT1, L"Поле №1", 10, 20, 150, 30);
	CreateStaticTextControl(IDC_ADDITEMDIALOG_STATIC_TEXT2, L"Поле №2", 10, 65, 150, 30);
	CreateStaticTextControl(IDC_ADDITEMDIALOG_STATIC_TEXT1, L"Поле №3", 10, 110, 150, 30);
	CreateStaticTextControl(IDC_ADDITEMDIALOG_STATIC_TEXT1, L"Поле №4", 10, 155, 150, 30);
	CreateStaticTextControl(IDC_ADDITEMDIALOG_STATIC_TEXT1, L"Поле №5", 10, 200, 150, 30);
	CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		180, 250, 120, 30, Window(), reinterpret_cast<HMENU>(ID_ADDITEMDIALOG_BUTTON_ADD),
		GetModuleHandle(nullptr), nullptr);
}


HWND EditItemDialog::CreateEditTextControl(DWORD id, int X, int Y, int nWidth, int nHeight, int textLength) {
	HWND hEdit = CreateWindowExW(
		WS_EX_CLIENTEDGE, L"EDIT",
		nullptr,
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL |
		ES_LEFT | WS_BORDER,
		X, Y, nWidth, nHeight,
		Window(),
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
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		X,
		Y,
		nWidth,
		nHeight,
		Window(),
		reinterpret_cast<HMENU>(id),
		GetModuleHandle(0),
		nullptr);

	return hStatic;
}


void EditItemDialog::CleanEditTextFields() {
	SetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT1), L"");
	SetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT2), L"");
	SetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT3), L"");
	SetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT4), L"");
	SetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT5), L"");
}


void EditItemDialog::OnButtonAdd() {
	wstring wstr[5]{};
	wstr[0].resize(GetWindowTextLength(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT1)));
	GetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT1), &wstr[0][0], wstr[0].size() + 1);
	wstr[1].resize(GetWindowTextLength(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT2)));
	GetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT2), &wstr[1][0], wstr[1].size() + 1);
	wstr[2].resize(GetWindowTextLength(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT3)));
	GetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT3), &wstr[2][0], wstr[2].size() + 1);
	wstr[3].resize(GetWindowTextLength(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT4)));
	GetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT4), &wstr[3][0], wstr[3].size() + 1);
	wstr[4].resize(GetWindowTextLength(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT5)));
	GetWindowText(GetDlgItem(Window(), ID_ADDITEMDIALOG_EDIT5), &wstr[4][0], wstr[4].size() + 1);

	if (wstr[0] == L"" || wstr[1] == L"" || wstr[2] == L"" || wstr[3] == L"" || wstr[4] == L"") {
		MessageBox(Window(), L"Всі поля повинні бути заповнені", L"Попередження", MB_OK | MB_ICONWARNING);
		return;
	}

	pData->push_back({ wstr[0], wstr[1], wstr[2], wstr[3], wstr[4] });
	MessageBox(Window(), L"Об'єкт успішно додано до таблиці!", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	CleanEditTextFields();
}