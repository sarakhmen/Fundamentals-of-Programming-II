#include "FindItemDialog.h"

FindItemDialog::FindItemDialog(HWND hwndParent, Data* pData) {
	parent = hwndParent;
	this->pData = pData;
}


FindItemDialog::~FindItemDialog() {
	if (m_hwnd)
		CloseHandle(m_hwnd);
}


PCWSTR FindItemDialog::ClassName() const {
	return L"Find item dialog";
}


LRESULT FindItemDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		OnCreate();
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_FINDITEMDIALOG_BUTTON1:
			OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL1, 0);
			break;
		case IDC_FINDITEMDIALOG_BUTTON2:
			OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL2, 1);
			break;
		case IDC_FINDITEMDIALOG_BUTTON3:
			OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL3, 2);
			break;
		case IDC_FINDITEMDIALOG_BUTTON4:
			OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL4, 3);
			break;
		case IDC_FINDITEMDIALOG_BUTTON5:
			OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL5, 4);
			break;
		}

		return 0;

	case WM_CLOSE:
		//CleanFindTextFields();
		endLoop = true;
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


void FindItemDialog::GetUserFind() {
	EnableWindow(parent, FALSE);
	ShowWindow(m_hwnd, SW_SHOW);
	MessageLoop();
	EnableWindow(parent, TRUE);
	ShowWindow(m_hwnd, SW_HIDE);
	SetFocus(parent);
}


void FindItemDialog::MessageLoop() {
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


void FindItemDialog::OnCreate() {
	PrintConsole(L"ON_CREATE\n");
	//check if creation is successful
	HWND hEdit = CreateWindowExW(
		WS_EX_CLIENTEDGE, L"EDIT",
		nullptr,
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL |
		ES_LEFT | WS_BORDER,
		10, 15, 260, 30,
		m_hwnd,
		reinterpret_cast<HMENU>(IDC_FINDITEMDIALOG_EDIT),
		GetModuleHandle(nullptr),
		nullptr);
	CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON1, L"Пошук в першій колонці", 10, 65, 260, 30);
	CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON2, L"Пошук в другій колонці", 10, 110, 260, 30);
	CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON3, L"Пошук в третій колонці", 10, 155, 260, 30);
	CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON4, L"Пошук в четвертій колонці", 10, 200, 260, 30);
	CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON5, L"Пошук в п'ятій колонці", 10, 245, 260, 30);
}


HWND FindItemDialog::CreateFindItemButton(DWORD id, LPCWSTR szStr, int X, int Y, int nWidth, int nHeight) {
	HWND hEdit = CreateWindow(L"BUTTON", szStr, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		X, Y, nWidth, nHeight, m_hwnd, reinterpret_cast<HMENU>(id),
		GetModuleHandle(nullptr), nullptr);
	return hEdit;
}


void FindItemDialog::OnButtonFind(DWORD id, int maxTextLength, int iColumn) {
	wstring wstr{};
	int fieldLength = GetWindowTextLength(GetDlgItem(m_hwnd, id));
	if (fieldLength > maxTextLength)
		fieldLength = maxTextLength;
	wstr.resize(fieldLength);
	GetWindowTextW(GetDlgItem(m_hwnd, id), &wstr[0], wstr.size() + 1);

	if (wstr == L"") {
		MessageBox(m_hwnd, L"Заповніть поле для вводу", L"Попередження", MB_OK | MB_ICONWARNING);
		return;
	}

	for (size_t i = 0; i < pData->size(); ++i) {
		if (_wcsnicmp(wstr.c_str(), (*pData)[i][iColumn].c_str(), fieldLength) == 0) {
			pData->pushMaskIndex(i);
			PrintConsole(L"finded " + (*pData)[i][iColumn] + L'\n');
		}
	}

	MessageBox(m_hwnd, L"Пошук виконано!", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	endLoop = true;
	//CleanFindTextFields();
}
