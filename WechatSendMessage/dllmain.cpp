// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "resource.h"
#include "WechatSendMessage.h"
DWORD WINAPI ThreadProc(
	_In_ HMODULE hModule
);

INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, hModule, 0, NULL);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD WINAPI ThreadProc(
	_In_ HMODULE hModule
)
{
	DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, &DialogProc);
	return TRUE;
}

INT_PTR CALLBACK DialogProc(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	char wxid[0x100] = { 0 };
	char message[0x100] = {0};
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg,0);
		break;
	case WM_COMMAND:
		if (wParam == SEND_TEXT) {
			GetDlgItemText(hwndDlg, WXID, wxid, sizeof(wxid));
			GetDlgItemText(hwndDlg, MESSAGE, message, sizeof(message));
			SendTextMessage(UTF8ToUnicode(wxid), UTF8ToUnicode(message));
		}
		if (wParam == SEND_PIC) {
			GetDlgItemText(hwndDlg, WXID, wxid, sizeof(wxid));
			GetDlgItemText(hwndDlg, MESSAGE, message, sizeof(message));
			sendPicMessage(UTF8ToUnicode(wxid), UTF8ToUnicode(message));
		}
		break;
	default:
		break;
	}
	return FALSE;
}