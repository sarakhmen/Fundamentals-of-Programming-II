#include "stdafx.h"
#include "MainWindow.h"


MainWindow::MainWindow() {
#ifdef _DEBUG
	AllocConsole();
#endif
}


MainWindow::~MainWindow() {
#ifdef _DEBUG
	FreeConsole();
#endif
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
		12, 10, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_LOAD_DATA), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 45, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_ADD_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Звіт", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 80, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_REPORT), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Видалити виділені", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 115, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_DEL_SELECTED), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Очистити таблицю", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 150, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_CLEAR), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if(!CreateWindow(L"BUTTON", L"Редагувати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 185, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_EDIT_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Пошук", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 220, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_FIND_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Зберегти", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		12, 255, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_SAVE), GetModuleHandle(nullptr), nullptr))
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
		MessageBox(nullptr, L"Не вдалося створити кнопки", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	pTable = new(nothrow) Table{ m_hwnd, IDC_TABLE, &data, TABLE_OFFSET_X };
	if (!pTable) {
		MessageBox(nullptr, L"Не вдалося виділити пам'ять під таблицю", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	addItemDialog = new(nothrow) AddItemDialog{ m_hwnd , &data};
	if (!addItemDialog) {
		MessageBox(nullptr, L"Не вдалося виділити пам'ять під вікно додавання нових елементів", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	if (!addItemDialog->Create(L"Додавання нового студента",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 400, 340, m_hwnd)) {
		MessageBox(nullptr, L"Не вдалося створити вікно додавання нових елементів", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	editItemDialog = new(nothrow) EditItemDialog{ m_hwnd , &data };
	if (!editItemDialog) {
		MessageBox(nullptr, L"Не вдалося виділити пам'ять під вікно редагування елементів", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	if (!editItemDialog->Create(L"Редагування",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 400
		, 340, m_hwnd)) {
		MessageBox(nullptr, L"Не вдалося створити вікно редагування елементів", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	findItemDialog = new(nothrow) FindItemDialog{ m_hwnd , &data };
	if (!findItemDialog) {
		MessageBox(nullptr, L"Не вдалося виділити пам'ять під вікно пошуку", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	if (!findItemDialog->Create(L"Пошук",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 297, 340, m_hwnd)) {
		MessageBox(nullptr, L"Не вдалося створити вікно пошуку", L"Помилка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	EnumChildWindows(m_hwnd, [](HWND child, LPARAM font){
		SendMessage(child, WM_SETFONT, font, true);
		return TRUE;
		}, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
}


void MainWindow::OnButtonAddItem() {
	addItemDialog->GetUserInput();
	pTable->UpdateItems();
}


void MainWindow::OnButtonEditItem() {
	int iItem = pTable->GetItemToEdit();
	if (iItem != -1) {
		editItemDialog->GetUserEdit(iItem);
		pTable->UpdateItems();
	}
}


void MainWindow::OnDeleteSelected() {
	pTable->DeleteSelected();
	pTable->UpdateItems();
}


void MainWindow::OnButtonClear() {
	if(data.relative_size() == 0)
		MessageBox(m_hwnd, L"Таблиця пуста", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	else if (MessageBox(m_hwnd, L"Ви дійсно хочете видалити всі елементи?",
		L"Підтвердження", MB_OKCANCEL) == IDOK) {
		data.clear();
		pTable->UpdateItems();
		MessageBox(m_hwnd, L"Всі елементи видалено", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
}


void MainWindow::OnButtonLoadData() {
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
		return;
	}

	//check extension
	wstring wstrExtension = L".kursach";
	size_t iPos{};
	if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {	//if extension specified
		if (wcscmp(&wstrFile[iPos], wstrExtension.c_str()) == 0) {	//and refers to our file
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
		return;
	}

	wstring wstrExtension = L".kursach";
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
			DeleteFile(wstring(ofn.lpstrFile + wstrExtension).c_str());
			PipeTableDataToFile(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {
		if (bExist) {
			if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
				L"Підтвердження", MB_OKCANCEL) == IDOK) {
				DeleteFile(ofn.lpstrFile);
				PipeTableDataToFile(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
			}
		}
		else {
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
	for (size_t i = 0; i < data.relative_size(); ++i) {
		for (size_t j = 0; j < data[0].size(); ++j) {
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
}


void MainWindow::OnButtonFindItem() {
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
}


void MainWindow::OnButtonReport() {
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
		return;
	}

	wstring wstrExtension = L".txt";
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
			DeleteFile(wstring(ofn.lpstrFile + wstrExtension).c_str());
			FormPeport(ofn.lpstrFile + wstrExtension, FILE_APPEND_DATA, OPEN_ALWAYS);
		}
	}
	else if ((iPos = wstrFile.rfind(wstrExtension)) != wstring::npos) {
		if (bExist) {
			if (MessageBox(m_hwnd, L"Ви дійсно хочете перезаписати вибраний файл?",
				L"Підтвердження", MB_OKCANCEL) == IDOK) {
				DeleteFile(ofn.lpstrFile);
				FormPeport(ofn.lpstrFile, FILE_APPEND_DATA, OPEN_ALWAYS);
			}
		}
		else {
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
	PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	for (size_t i = 0; i < data.relative_size(); ++i) {
		wstrOut.replace(0, strOutLen, strOutLen, L'-');
		PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
		wstrOut.clear();
		wstrOut += L'|';
		for (size_t j = 0; j < data[i].size(); ++j) {
			wstrTemp = data[i][j];
			wstrTemp.resize(MAX_STR_LEN_COL[j], L' ');
			wstrOut += wstrTemp + L'|';
		}
		PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	}
	wstrOut.replace(0, strOutLen, strOutLen, L'-');
	PutFileContent(wcstFileName, wstrOut + L'\n', dwDesiredAccess, dwCreationDisposition);
	ShellExecuteW(NULL, NULL, wcstFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

