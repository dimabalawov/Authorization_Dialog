#pragma once
#include "header.h"

class LoginModalDialog
{
public:
	LoginModalDialog(void);
	LoginModalDialog(LPCTSTR lpStr);
public:
	~LoginModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static LoginModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	TCHAR text[200];
	HWND hEdit2, hEdit4;
};