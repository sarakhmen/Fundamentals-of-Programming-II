#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>

#include "BaseWindow.h"
#include "MainWindow.h"
#include "FileReadWrite.h"
#include "Resource.h"

using namespace std;

//
//HWND CreateListView(HWND hwndParent)
//{
//	INITCOMMONCONTROLSEX icex;
//	icex.dwICC = ICC_LISTVIEW_CLASSES;
//	InitCommonControlsEx(&icex);
//
//	RECT rcClient;
//
//	GetClientRect(hwndParent, &rcClient);
//	HWND hWndListView = CreateWindow(WC_LISTVIEW,
//		L"",
//		WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
//		200, 0,
//		rcClient.right - rcClient.left,
//		rcClient.bottom - rcClient.top,
//		hwndParent,
//		(HMENU)101,
//		NULL,
//		NULL);
//
//	return (hWndListView);
//}
//
//BOOL InitListViewColumns(HWND hWndListView)
//{
//	WCHAR szText[256] = L"NAMECOLUMN";
//	LVCOLUMN lvc;
//	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//	lvc.iSubItem = 0;
//	lvc.pszText = szText;
//	lvc.cx = 100;
//	lvc.fmt = LVCFMT_LEFT;
//	if (ListView_InsertColumn(hWndListView, 0, &lvc) == -1)
//		return FALSE;
//	return TRUE;
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	//locale::global(locale(".UTF16"));
	//_wsetlocale(LC_ALL, L".UTF8");

	//wstring fileName = L"C:\\Users\\Sarahman\\Desktop\\test.txt";
	//wstring wstBuffer;
	//PutFileContent(fileName, L"something", FILE_APPEND_DATA);
	//if (GetFileContent(fileName, wstBuffer)) {
	//	PrintConsole(wstBuffer);
	//	PrintConsole(L"\nREALLY WORKS\n");
	//}
	//else {
	//	PrintConsole(L"\nFAILED\n");
	//}

	MainWindow myWnd;

	if (!myWnd.Create(L"Hostel administrator", WS_OVERLAPPEDWINDOW, 0, 500, 300, 700, 480))
		return 0;

	ShowWindow(myWnd.Window(), nCmdShow);
	//HWND hListView = CreateListView(myWnd.m_hwnd);
	//if (hListView == NULL)
	//	PrintConsole(L"ERROR");
	//ShowWindow(hListView, nCmdShow);
	//InitListViewColumns(hListView);

	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}








//read/write
//AllocConsole();
//HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
//
//if (stdOut == NULL || stdOut == INVALID_HANDLE_VALUE || stdIn == NULL || stdIn == INVALID_HANDLE_VALUE) {
//	return 1;
//}
//
//HANDLE hFile = CreateFile(
//	L"C:\\Users\\Sarahman\\Desktop\\NewFile.txt",
//	FILE_APPEND_DATA,
//	FILE_SHARE_READ,
//	NULL,
//	OPEN_ALWAYS,
//	FILE_ATTRIBUTE_NORMAL,
//	NULL);
//
//if (FAILED(hFile))
//{
//	wstring mes = L"ouch\n";
//	WriteConsole(stdOut, mes.c_str(), mes.relative_size(), nullptr, nullptr);
//	system("pause");
//	return 2;
//}
//
//wstring strText = L"חהמנמג ן³םדג³ם how are you \u0302\u0405";
//DWORD bytesWritten;
//WriteFile(
//	hFile,
//	strText.c_str(),
//	strText.relative_size() * sizeof(WCHAR),
//	&bytesWritten,
//	nullptr);
//WriteConsole(stdOut, strText.c_str(), strText.length(), &bytesWritten, nullptr);
//CloseHandle(hFile);
//
//WCHAR buf[256]{};
//hFile = CreateFile(
//	L"C:\\Users\\Sarahman\\Desktop\\NewFile.txt",
//	GENERIC_READ,
//	FILE_SHARE_WRITE,
//	NULL,
//	OPEN_ALWAYS,
//	FILE_ATTRIBUTE_NORMAL,
//	NULL);
//
//vector <PWSTR> vec;
//vec.push_back(new WCHAR[5]{});
//size_t i = 0;
//while (ReadFile(hFile, reinterpret_cast<LPVOID>(vec[i]), 4 * sizeof(WCHAR), &bytesWritten, nullptr) && bytesWritten > 0) {
//	WriteConsole(stdOut, L"\nGOCHA\n", 7, &bytesWritten, nullptr);
//	WriteConsole(stdOut, vec[i], wcslen(vec[i]), &bytesWritten, nullptr);
//	vec.push_back(new WCHAR[5]{});
//	i++;
//}
//WriteConsole(stdOut, L"\nYEAHH\n", 7, &bytesWritten, nullptr);
//for (size_t j = 0; j < i; j++) {
//	WriteConsole(stdOut, vec[j], wcslen(vec[j]), &bytesWritten, nullptr);
//}
//
////for (size_t i = 0; buf[i] != L'\0'; i++) {
////	if (iswalpha(buf[i])) {
////		WriteConsole(stdOut, buf + i, 1, &bytesWritten, nullptr);
////		WriteConsole(stdOut, L"\t", 1, &bytesWritten, nullptr);
////	}
////}
////WriteConsole(stdOut, buf, wcslen(buf), &bytesWritten, nullptr);
//
////HANDLE outF = CreateFile(
////	L"C:\\Users\\Sarahman\\Desktop\\NewFile.txt",     
////	FILE_APPEND_DATA,   
////	FILE_SHARE_READ,  
////	NULL,           
////	OPEN_ALWAYS,
////	FILE_ATTRIBUTE_NORMAL, 
////	NULL); 
////if (FAILED(outF)) {
////	WriteConsole(stdOut, L"\nfailed\n", 8, &bytesWritten, nullptr);
////	return 2;
////}
////WriteFile(outF, reinterpret_cast<LPVOID>(buf), wcslen(buf) * sizeof(WCHAR), &bytesWritten, nullptr);
//CloseHandle(hFile);
////CloseHandle(outF);
//CloseHandle(stdOut);
//CloseHandle(stdIn);
//
//































//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <Windows.h>
//
////using namespace std;
////
////class Data_base {
////public:
////	Data_base();
////	Data_base(string filename, char field_separator = ';');
////	//~Data_base();
////
////private:
////	string filename;
////	vector<string> file_content;
////	char field_separator;
////};
////
////Data_base::Data_base(string filename, char field_separator) {
////
////}
////
////
//////Data_base::~Data_base() {
//////
//////}
////
////
////int main(int argc, char *argv[])
////{
////	cout << "start" << endl;
////	cout << "end";
////	return 0;
////}


