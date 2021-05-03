#include "MainWindow.h"


MainWindow::MainWindow() {
	AllocConsole();
}


MainWindow::~MainWindow() {
	FreeConsole();
	if (pTable)
		delete pTable;
	if (addItemDialog) {
		DestroyWindow(addItemDialog->Window());
		delete addItemDialog;
	}
	if (editItemDialog) {
		DestroyWindow(editItemDialog->Window());
		delete editItemDialog;
	}
	if (findItemDialog) {
		DestroyWindow(findItemDialog->Window());
		delete findItemDialog;
	}
}


PCWSTR MainWindow::ClassName() const {
	return L"Workplace automatization";
}


LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		OnCreate();
		return 0;

	case WM_SIZE:
		pTable->ResizeTable();
		return 0;

	case WM_NOTIFY:
		return pTable->TableNotify(lParam);

	case WM_COMMAND:
		OnButtonClicked(wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SETFOCUS:
		SetFocus(pTable->GetListViewHandle());
		break;
	}

	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


BOOL MainWindow::CreateButtons() {
	if (!CreateWindow(L"BUTTON", L"Завантажити дані", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 10, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_LOAD_DATA), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 45, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_ADD_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Звіт", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 80, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_REPORT), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Видалити виділені", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 115, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_DEL_SELECTED), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Очистити таблицю", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 150, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_CLEAR), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if(!CreateWindow(L"BUTTON", L"Редагувати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 185, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_EDIT_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Пошук", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 220, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_FIND_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Зберегти", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 255, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_SAVE), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	return TRUE;
}


void MainWindow::OnButtonClicked(WPARAM wParam, LPARAM lParam) {
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_LOAD_DATA:
		OnButtonLoadData();
		break;

	case IDC_BUTTON_ADD_ITEM:
		OnButtonAddItem();
		break;

	case IDC_BUTTON_REPORT:
		OnButtonReport();
		break;

	case IDC_BUTTON_DEL_SELECTED:
		OnDeleteSelected();
		break;

	case IDC_BUTTON_EDIT_ITEM:
		OnButtonEditItem();
		break;

	case IDC_BUTTON_CLEAR:
		OnButtonClear();
		break;

	case IDC_BUTTON_FIND_ITEM:
		OnButtonFindItem();
		break;

	case IDC_BUTTON_SAVE:
		OnButtonSaveData();
		break;
	}
}


void MainWindow::OnCreate() {
	if (!CreateButtons()) {
		PrintConsole(L"Error while creating buttons\n");
		system("pause");
		PostQuitMessage(0);
	}
	pTable = new Table{ m_hwnd, IDC_TABLE, &data, TABLE_OFFSET_X };
	addItemDialog = new AddItemDialog{ m_hwnd , &data};
	if (!addItemDialog->Create(L"Add item", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 500, 340, m_hwnd))
		PrintConsole(L"Error while creating AddItemDialog\n");
	editItemDialog = new EditItemDialog{ m_hwnd , &data };
	if (!editItemDialog->Create(L"Edit item",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 500, 340, m_hwnd))
		PrintConsole(L"Error while creating EditItemDialog\n");
	findItemDialog = new FindItemDialog{ m_hwnd , &data };
	if (!findItemDialog->Create(L"Find item",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 500, 340, m_hwnd))
		PrintConsole(L"Error while creating FindItemDialog\n");
}


void MainWindow::OnButtonAddItem() {
	PrintConsole(L"AddItemDialog created\n");
	addItemDialog->GetUserInput();
	pTable->UpdateItems();
	PrintConsole(L"AddItemDialog destroyed\n");
}


void MainWindow::OnButtonEditItem() {
	PrintConsole(L"EditItemDialog created\n");
	int iItem = pTable->GetItemToEdit();
	if (iItem != -1) {
		editItemDialog->GetUserEdit(iItem);
		pTable->UpdateItems();
	}
	PrintConsole(L"EditItemDialog destroyed\n");
}


void MainWindow::OnDeleteSelected() {
	PrintConsole(L"Delete selected start\n");
	pTable->DeleteSelected();
	pTable->UpdateItems();
	PrintConsole(L"Delete selected fineshed\n");
}


void MainWindow::OnButtonClear() {
	PrintConsole(L"Clear start\n");
	if(data.relative_size() == 0)
		MessageBox(m_hwnd, L"Таблиця пуста", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	else if (MessageBox(m_hwnd, L"Ви дійсно хочете видалити всі елементи?",
		L"Підтвердження", MB_OKCANCEL) == IDOK) {
		data.clear();
		pTable->UpdateItems();
		MessageBox(m_hwnd, L"Всі елементи видалено", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
	PrintConsole(L"Clear fineshed\n");
}


void MainWindow::OnButtonLoadData() {
	PrintConsole(L"Loading table blah blah blah...\n");
	if(data.isMask()){
		MessageBox(m_hwnd, L"Закінчте пошук перед тим як завантажити нові дані!", L"Помилка", MB_OK | MB_ICONERROR);
		return;
	}
	OPENFILENAME ofn{};
	wstring wstrFile;
	wstrFile.resize(MAX_PATH);
	WCHAR szCurrentDir[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szCurrentDir) / sizeof(szCurrentDir[0]) - 1, szCurrentDir);
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hwnd;
	ofn.lpstrFile = &wstrFile[0];
	ofn.nMaxFile = wstrFile.size();
	ofn.lpstrFilter = L"Data table (*.kursach)\0*.kursach*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = szCurrentDir;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) != TRUE){
		PrintConsole(L"Error while invoking GetOpenFileName\n");
		return;
	}

	PrintConsole(ofn.lpstrFile);
	//check extension
	wstring wstrExtension = L".kursach";
	size_t iPos{};
	if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {	//if extension specified
		if (wcscmp(&wstrFile[iPos], wstrExtension.c_str()) == 0) {	//and refers to our file
			PrintConsole(L"Reading\n");
			wstring wstBuffer{};
			data.clear();
			GetFileContent(ofn.lpstrFile, wstBuffer);
			ConstructTable(wstBuffer);
			pTable->UpdateItems();
		}
		else
			MessageBox(m_hwnd, L"Неможливо зчитати дані з файлу з подібним розширенням", L"Помилка", MB_OK | MB_ICONERROR);
	}
	else
		MessageBox(m_hwnd, L"Неможливо зчитати дані з файлу з подібним розширенням", L"Помилка", MB_OK | MB_ICONERROR);
}


void MainWindow::OnButtonSaveData() {
	PrintConsole(L"Saving...\n");
	OPENFILENAME ofn{};
	wstring wstrFile;
	wstrFile.resize(MAX_PATH);
	WCHAR szCurrentDir[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szCurrentDir) / sizeof(szCurrentDir[0]) - 1, szCurrentDir);
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hwnd;
	ofn.lpstrFile = &wstrFile[0];
	ofn.nMaxFile = wstrFile.size();
	ofn.lpstrFilter = L"Data table (*.kursach)\0*.kursach*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = szCurrentDir;
	ofn.Flags = OFN_PATHMUSTEXIST;

	if (GetSaveFileName(&ofn) != TRUE){
		PrintConsole(L"Error while invoking GetSaveFileName\n");
		return;
	}

	wstring wstrExtension = L".kursach";
	//check if chosen file exist
	BOOL bExist = FALSE;
	BOOL bKursachFileExist = FALSE;
	DWORD dwAttrib = GetFileAttributes(ofn.lpstrFile);
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
			bExist = TRUE;
	dwAttrib = GetFileAttributes(wstring(ofn.lpstrFile + wstrExtension).c_str());
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		bKursachFileExist = TRUE;

	size_t iPos{};
	if (bKursachFileExist == TRUE) {
		if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
			L"Підтвердження", MB_OKCANCEL) == IDOK) {
			PrintConsole(L"Rewriting\n");
			DeleteFile(wstring(ofn.lpstrFile + wstrExtension).c_str());
			PipeTableDataToFile(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {
		if (bExist) {
			if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
				L"Підтвердження", MB_OKCANCEL) == IDOK) {
				PrintConsole(L"Rewriting\n");
				DeleteFile(ofn.lpstrFile);
				PipeTableDataToFile(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
			}
		}
		else {
			PrintConsole(L"Writing\n");
			DeleteFile(ofn.lpstrFile);
			PipeTableDataToFile(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if (bExist) {
		MessageBox(m_hwnd, L"Неправильно вибрано файл для збереження", L"Помилка", MB_OK | MB_ICONERROR);
	}
	else
		PipeTableDataToFile(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
}


void MainWindow::PipeTableDataToFile(const wstring& wcstFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition) {
	PrintConsole(wcstFileName + L'\n');
	for (size_t i = 0; i < data.relative_size(); ++i) {
		for (size_t j = 0; j < data[0].size(); ++j) {
			PrintConsole(data[i][j] + L'\n');
			PutFileContent(wcstFileName, data[i][j] + L'\n', dwDesiredAccess, dwCreationDisposition);
		}
	}
}


void MainWindow::ConstructTable(const wstring& wcstBuffer) {
	size_t wstSize = wcstBuffer.size();
	size_t iPosPrev{},
		iPosNext{};

	iPosNext = wcstBuffer.find(L'\n', iPosPrev);
	for (size_t i = 0; iPosNext < wstSize - 1; ++i) { //which corresponds to the file content syntax
		data.pushBack(vector<wstring>{});
		for (size_t j = 0; (iPosNext < (wstSize - 1)) && (j < TABLE_COL_NUMBER); ++j) {
			data[i].push_back(wcstBuffer.substr(iPosPrev, iPosNext - iPosPrev));
			iPosPrev = iPosNext + 1;
			iPosNext = wcstBuffer.find(L'\n', iPosPrev);
		}
	}
	PrintConsole(L"Table created");
}


void MainWindow::OnButtonFindItem() {
	PrintConsole(L"FindItemDialog created\n");
	if (data.real_size() == 0) {
		MessageBox(m_hwnd, L"Таблиця пуста", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
	else if (!data.isMask()) {
		SetWindowText(GetDlgItem(m_hwnd, IDC_BUTTON_FIND_ITEM), L"Закінчити пошук");
		findItemDialog->GetUserFind();
		data.setMask(true);
		pTable->UpdateItems();
	}
	else {
		SetWindowText(GetDlgItem(m_hwnd, IDC_BUTTON_FIND_ITEM), L"Пошук");
		data.setMask(false);
		pTable->UpdateItems();
	}
	PrintConsole(L"FindItemDialog destroyed\n");
}


void MainWindow::OnButtonReport() {
	PrintConsole(L"Reporting...\n");
	OPENFILENAME ofn{};
	wstring wstrFile;
	wstrFile.resize(MAX_PATH);
	WCHAR szCurrentDir[MAX_PATH]{};
	GetCurrentDirectory(sizeof(szCurrentDir) / sizeof(szCurrentDir[0]) - 1, szCurrentDir);
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hwnd;
	ofn.lpstrFile = &wstrFile[0];
	ofn.nMaxFile = wstrFile.size();
	ofn.lpstrFilter = L"Text files (*.txt)\0*.txt*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = szCurrentDir;
	ofn.Flags = OFN_PATHMUSTEXIST;

	if (GetSaveFileName(&ofn) != TRUE) {
		PrintConsole(L"Error while invoking GetSaveFileName\n");
		return;
	}

	wstring wstrExtension = L".txt";
	//check if chosen file exist
	BOOL bExist = FALSE;
	BOOL bTxtFileExist = FALSE;
	DWORD dwAttrib = GetFileAttributes(ofn.lpstrFile);
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		bExist = TRUE;
	dwAttrib = GetFileAttributes(wstring(ofn.lpstrFile + wstrExtension).c_str());
	if (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
		bTxtFileExist = TRUE;

	size_t iPos{};
	if (bTxtFileExist == TRUE) {
		if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
			L"Підтвердження", MB_OKCANCEL) == IDOK) {
			PrintConsole(L"Rewriting\n");
			DeleteFile(wstring(ofn.lpstrFile + wstrExtension).c_str());
			FormPeport(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {
		if (bExist) {
			if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
				L"Підтвердження", MB_OKCANCEL) == IDOK) {
				PrintConsole(L"Rewriting\n");
				DeleteFile(ofn.lpstrFile);
				FormPeport(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
			}
		}
		else {
			PrintConsole(L"Writing\n");
			DeleteFile(ofn.lpstrFile);
			FormPeport(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if (bExist) {
		MessageBox(m_hwnd, L"Неправильно вибрано файл для збереження", L"Помилка", MB_OK | MB_ICONERROR);
	}
	else
		FormPeport(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
}


void MainWindow::FormPeport(const wstring& wcstFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition) {
	PrintConsole(wcstFileName + L'\n');
	wstring wstrText;
	wstrText.resize(MAX_PATH);
	LVCOLUMN lvc{};
	lvc.mask = LVCF_TEXT;
	lvc.pszText = &wstrText[0];
	lvc.cchTextMax = MAX_PATH;

	wstring wstrOut{};
	wstring wstrTemp{};
	int strOutLen{ 1 };	//1 for left border
	for (int i = 0; i < TABLE_COL_NUMBER; ++i)
		strOutLen += MAX_STR_LEN_COL[i] + 1;
	wstrOut.replace(0, strOutLen, strOutLen, L'-');
	PrintConsole(wstrOut);
	PutFileContent(wcstFileName,wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	wstrOut.clear();
	wstrOut += L'|';
	for (int i = 0; i < TABLE_COL_NUMBER; ++i) {
		ListView_GetColumn(pTable->GetListViewHandle(), i, &lvc);
		wstrTemp = lvc.pszText;
		wstrTemp.resize(MAX_STR_LEN_COL[i], L' ');	//to fill missing characters and align output
		wstrOut += wstrTemp;
		wstrOut += L'|';
	}
	PrintConsole(wstrOut);
	PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	for (size_t i = 0; i < data.relative_size(); ++i) {
		wstrOut.replace(0, strOutLen, strOutLen, L'-');
		PrintConsole(wstrOut);
		PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
		wstrOut.clear();
		wstrOut += L'|';
		for (size_t j = 0; j < data[i].size(); ++j) {
			wstrTemp = data[i][j];
			wstrTemp.resize(MAX_STR_LEN_COL[j], L' ');
			wstrOut += wstrTemp + L'|';
		}
		PrintConsole(wstrOut);
		PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	}
	wstrOut.replace(0, strOutLen, strOutLen, L'-');
	PrintConsole(wstrOut);
	PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	ShellExecuteW(NULL, NULL, wcstFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}