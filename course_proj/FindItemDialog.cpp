#include "stdafx.h"
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
	{
		WORD buttonId = LOWORD(wParam);
		for (int i = 0; i < TABLE_COL_NUMBER; ++i) {
			if (buttonId == IDC_FINDITEMDIALOG_BUTTON_0 + i) {
				OnButtonFind(IDC_FINDITEMDIALOG_EDIT, MAX_STR_LEN_COL[i], i);
				break;
			}
		}
	}
	return 0;

	case WM_CLOSE:
		//CleanFindTextFields();
		PostMessage(parent, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_FIND_ITEM, 0), 
			reinterpret_cast<LPARAM>(GetDlgItem(parent, IDC_BUTTON_FIND_ITEM))); //to end search properly
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
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void FindItemDialog::OnCreate() {
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

	wstring wstr[TABLE_COL_NUMBER] = { FIND_LABEL_0, FIND_LABEL_1, FIND_LABEL_2, FIND_LABEL_3, FIND_LABEL_4 };
	for(int i = 0; i < TABLE_COL_NUMBER; ++i)
		CreateFindItemButton(IDC_FINDITEMDIALOG_BUTTON_0 + i, wstr[i].c_str(), 10, 65 + i*45, 260, 30);
	
	EnumChildWindows(m_hwnd, [](HWND child, LPARAM font) {
		SendMessage(child, WM_SETFONT, font, true);
		return TRUE;
		}, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
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

	for (size_t i = 0; i < pData->relative_size(); ++i) {
		if (_wcsnicmp(wstr.c_str(), (*pData)[i][iColumn].c_str(), fieldLength) == 0) {
			pData->pushMaskIndex(i);
		}
	}

	MessageBox(m_hwnd, L"Пошук виконано!", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	endLoop = true;
	//CleanFindTextFields();
}
