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
		pTable->ResizeTable(Window());
		return 0;

	case WM_NOTIFY:
		return pTable->TableNotify(lParam);

	case WM_COMMAND:
		OnButtonClicked(wParam, lParam);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}


BOOL MainWindow::CreateButtons() {
	HWND hWnd = Window();
	if (!CreateWindow(L"BUTTON", L"Додати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 10, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON_ADD_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Звіт", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 45, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON2), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Видалити", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 80, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON3), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if(!CreateWindow(L"BUTTON", L"Редагувати", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 115, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON_EDIT_ITEM), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Пошук", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 150, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON5), GetModuleHandle(nullptr), nullptr))
		return FALSE;
	if (!CreateWindow(L"BUTTON", L"Зберегти", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		10, 185, 100, 25, hWnd, reinterpret_cast<HMENU>(ID_BUTTON6), GetModuleHandle(nullptr), nullptr))
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
		break;

	case ID_BUTTON3:
		PrintConsole(L"BUTTON3 pressed\n");
		break;

	case ID_BUTTON_EDIT_ITEM:
		OnButtonEditItem();
		break;

	case ID_BUTTON5:
		PrintConsole(L"BUTTON5 pressed\n");
		break;

	case ID_BUTTON6:
		PrintConsole(L"BUTTON6 pressed\n");
		MessageBox(Window(),
			L"Functionality isn't implemented",
			L"Error while clicking",
			MB_ICONERROR);
		PrintConsole(L"Message box went on\n");
		break;
	}
}


void MainWindow::OnCreate() {
	if (!CreateButtons()) {
		PrintConsole(L"Error while creating buttons\n");
		system("pause");
		PostQuitMessage(0);
	}
	pTable = new Table{ Window(), ID_TABLE };
	addItemDialog = new AddItemDialog{ Window() , &pTable->GetData()};
	if (!addItemDialog->Create(L"Add item", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 600, 350, 500, 340, Window()))
		PrintConsole(L"Error while creating AddItemDialog\n");
	editItemDialog = new EditItemDialog{ Window() , &pTable->GetData() };
	if (!editItemDialog->Create(L"Edit item",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 600, 350, 500, 340, Window()))
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
	editItemDialog->GetUserInput();
	pTable->UpdateItems();
	PrintConsole(L"EditItemDialog destroyed\n");
}
