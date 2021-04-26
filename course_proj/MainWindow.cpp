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
	if (!CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 10, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON_ADD_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Звіт", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 45, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON2), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Видалити виділені", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 80, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON_DEL_SELECTED), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Очистити таблицю", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 115, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(IDC_BUTTON_CLEAR), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if(!CreateWindow(L"BUTTON", L"Редагувати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 150, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON_EDIT_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Пошук", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 185, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON5), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Зберегти", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 220, BUTTONS_WIDTH, BUTTONS_HEIGHT, m_hwnd, reinterpret_cast<HMENU>(ID_BUTTON6), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	return TRUE;
}


void MainWindow::OnButtonClicked(WPARAM wParam, LPARAM lParam) {
	switch (LOWORD(wParam)) {
	case ID_BUTTON_ADD_ITEM:
		OnButtonAddItem();
		break;

	case ID_BUTTON2:
		PrintConsole(L"BUTTON2 pressed\n");
		MessageBox(m_hwnd,
			L"Functionality isn't implemented",
			L"Error while clicking",
			MB_ICONERROR);
		break;

	case ID_BUTTON_DEL_SELECTED:
		OnDeleteSelected();
		break;

	case ID_BUTTON_EDIT_ITEM:
		OnButtonEditItem();
		break;

	case IDC_BUTTON_CLEAR:
		OnButtonClear();
		break;

	case ID_BUTTON5:
		PrintConsole(L"BUTTON5 pressed\n");
		MessageBox(m_hwnd,
			L"Functionality isn't implemented",
			L"Error while clicking",
			MB_ICONERROR);
		break;

	case ID_BUTTON6:
		PrintConsole(L"BUTTON6 pressed\n");
		MessageBox(m_hwnd,
			L"Functionality isn't implemented",
			L"Error while clicking",
			MB_ICONERROR);
		break;
	}
}


void MainWindow::OnCreate() {
	if (!CreateButtons()) {
		PrintConsole(L"Error while creating buttons\n");
		system("pause");
		PostQuitMessage(0);
	}
	pTable = new Table{ m_hwnd, ID_TABLE, TABLE_OFFSET_X };
	addItemDialog = new AddItemDialog{ m_hwnd , &pTable->GetData()};
	if (!addItemDialog->Create(L"Add item", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 500, 340, m_hwnd))
		PrintConsole(L"Error while creating AddItemDialog\n");
	editItemDialog = new EditItemDialog{ m_hwnd , &pTable->GetData() };
	if (!editItemDialog->Create(L"Edit item",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 600, 350, 500, 340, m_hwnd))
		PrintConsole(L"Error while creating EditItemDialog\n");
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
	if(pTable->GetData().size() == 0)
		MessageBox(m_hwnd, L"Таблиця пуста", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	else if (MessageBox(m_hwnd, L"Ви дійсно хочете видалити всі елементи?",
		L"Підтвердження", MB_OKCANCEL) == IDOK) {
		pTable->ClearData();
		pTable->UpdateItems();
		MessageBox(m_hwnd, L"Всі елементи видалено", L"Повідомлення", MB_OK | MB_ICONINFORMATION);
	}
	PrintConsole(L"Clear fineshed\n");
}
