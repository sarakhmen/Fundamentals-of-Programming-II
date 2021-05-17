#include "stdafx.h"
#include "BaseWindow.h"
#include "MainWindow.h"
#include "FileReadWrite.h"
#include "Resource.h"

using namespace std;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MainWindow myWnd;

	if (!myWnd.Create(L"��������� ��������", WS_OVERLAPPEDWINDOW, 0, 500, 300, 800, 490)) {
		MessageBox(nullptr, L"�� ������� �������� ������� ����", L"�������", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(myWnd.Window(), nCmdShow);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}