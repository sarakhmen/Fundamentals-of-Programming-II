#ifndef _FILE_READ_WRITE_H
#define _FILE_READ_WRITE_H

using namespace std;

size_t GetFileContent(const wstring& cstFileName, wstring& wstBuffer);
size_t PutFileContent(const wstring& wcstFileName, const wstring& wstBuffer, DWORD dwDesiredAccess, DWORD dwCreationDisposition);
BOOL PrintConsole(const wstring& wstBuffer);

#endif 