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
		case ID_EDITITEMDIALOG_BUTTON_EDIT:
			OnButtonEdit();
			break;
		}
		return 0;

	case WM_CLOSE:
		//CleanEditTextFields();
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
	CreateEditTextControl(IDC_EDIT1, 200, 15, 260, 30, MAX_STR_LEN_COL0);
	CreateEditTextControl(IDC_EDIT2, 200, 60, 260, 30, MAX_STR_LEN_COL1);
	CreateEditTextControl(IDC_EDIT3, 200, 105, 260, 30, MAX_STR_LEN_COL2);
	CreateEditTextControl(IDC_EDIT4, 200, 150, 260, 30, MAX_STR_LEN_COL3);
	CreateEditTextControl(IDC_EDIT5, 200, 195, 260, 30, MAX_STR_LEN_COL4);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT1, L"���� �1", 10, 20, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT2, L"���� �2", 10, 65, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT3, L"���� �3", 10, 110, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT4, L"���� �4", 10, 155, 150, 30);
	CreateStaticTextControl(IDC_ITEMDIALOG_STATIC_TEXT5, L"���� �5", 10, 200, 150, 30);
	CreateWindow(L"BUTTON", L"����������", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		180, 250, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_EDITITEMDIALOG_BUTTON_EDIT),
		GetModuleHandle(nullptr), nullptr);
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


void EditItemDialog::CleanEditTextFields() {
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT1), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT2), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT3), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT4), L"");
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT5), L"");
}


void EditItemDialog::OnButtonEdit() {
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
		MessageBox(m_hwnd, L"�� ���� ������� ���� ���������", L"������������", MB_OK | MB_ICONWARNING);
		return;
	}

	(*pData)[iItemToEdit] = { wstr[0], wstr[1], wstr[2], wstr[3], wstr[4] };
	MessageBox(m_hwnd, L"��'��� ������ ������!", L"�����������", MB_OK | MB_ICONINFORMATION);
	endLoop = true;
	//CleanEditTextFields();
}


void EditItemDialog::InitializeContent(int iItem) {
	//for (size_t i = 0; i < pData->at(iItem).relative_size(); ++i) {
	//	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT1 + i), pData->at(iItem)[i].c_str());
	//}
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT1), (*pData)[iItem][0].c_str());
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT2), (*pData)[iItem][1].c_str());
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT3), (*pData)[iItem][2].c_str());
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT4), (*pData)[iItem][3].c_str());
	SetWindowText(GetDlgItem(m_hwnd, IDC_EDIT5), (*pData)[iItem][4].c_str());
}