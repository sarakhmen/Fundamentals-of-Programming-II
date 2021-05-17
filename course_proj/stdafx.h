#ifndef _H_STDAFX
#define _H_STDAFX

//provides a modern look
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib,"Comctl32.lib")

#include <Windows.h>
#include <CommCtrl.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include "BaseWindow.h"

#endif