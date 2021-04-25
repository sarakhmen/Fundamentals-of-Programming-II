#ifndef _FILE_READ_WRITE_H
#define _FILE_READ_WRITE_H
#include <Windows.h>
#include <string>
using namespace std;

size_t GetFileContent(const wstring& cstFileName, wstring& wstBuffer);
size_t PutFileContent(const wstring& cstFileName, const wstring& wstBuffer, DWORD dwDesiredAccess);
BOOL PrintConsole(const wstring& wstBuffer);

#endif 