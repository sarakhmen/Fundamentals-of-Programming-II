#include "stdafx.h"
#include "FileReadWrite.h"

size_t GetFileContent(const wstring& cstFileName, wstring& wstBuffer)
{
	HANDLE hFile = CreateFile(cstFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	DWORD dwBytesRead = 0;
	if (hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize = GetFileSize(hFile, nullptr);
		wstBuffer.resize(dwFileSize / sizeof(wchar_t) + 1);	//so that the logic doesn't brake
		if (ReadFile(hFile, &wstBuffer[0], dwFileSize, &dwBytesRead, nullptr)) {
			if (wstBuffer[0] == L'\uFEFF' || wstBuffer[0] == L'\uFFFE')
				wstBuffer.erase(0, 1);
		}
		CloseHandle(hFile);
	}
	return dwBytesRead;
}

size_t PutFileContent(const wstring& wcstFileName, const wstring& wstBuffer, DWORD dwDesiredAccess, DWORD dwCreationDisposition) {
	HANDLE hFile = CreateFileW(wcstFileName.c_str(), dwDesiredAccess, FILE_SHARE_READ, nullptr, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
	DWORD dwBytesWrite = 0;
	if (hFile != INVALID_HANDLE_VALUE) {
		WriteFile(hFile, &wstBuffer[0], wstBuffer.size() * sizeof(wchar_t), &dwBytesWrite, nullptr);
		CloseHandle(hFile);
	}
	return dwBytesWrite;
}

//useful in debug
BOOL PrintConsole(const wstring& wstBuffer) {
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL result = 0;
	if (stdOut != INVALID_HANDLE_VALUE) {
		result = WriteConsole(stdOut, wstBuffer.c_str(), wstBuffer.size(), nullptr, nullptr);
	}
	return result;
}