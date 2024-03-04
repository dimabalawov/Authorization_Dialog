#include "AdditionalModalDialog.h"
#include <fstream>
using namespace std;

HHOOK hHook;
HINSTANCE hMod;
bool hookFlag = 0;
HWND mainhwnd;

CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
}

CAdditionalModalDialog::CAdditionalModalDialog(LPCTSTR lpStr)
{
	ptr = this;
    _tcscpy(text, lpStr);
}

CAdditionalModalDialog::~CAdditionalModalDialog(void)
{
    UnhookWindowsHookEx(hHook);
}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if ((nCode == HC_ACTION) && (wParam == WM_LBUTTONDOWN))
    {
        if (hookFlag)
        {
            wofstream dataBaseFull("databaseFull.txt", ios::out | ios::trunc);
            dataBaseFull << "";
            TCHAR Login[30], Password[30], Name[30], Age[5];
            HWND hEdit1 = GetDlgItem(mainhwnd, IDC_EDIT1);
            HWND hEdit3 = GetDlgItem(mainhwnd, IDC_EDIT3);
            HWND hAge = GetDlgItem(mainhwnd, IDC_AGE);
            HWND hName = GetDlgItem(mainhwnd, IDC_NAME);
            GetWindowText(hEdit1, Login, 30);
            GetWindowText(hEdit3, Password, 30);
            GetWindowText(hName, Name, 30);
            GetWindowText(hAge, Age, 5);
            dataBaseFull << Login << endl;
            dataBaseFull << Password << endl;
            dataBaseFull << Name << endl;
            dataBaseFull << Age << endl;
            dataBaseFull.close();
        }
        return 0;
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    hHook = SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
    hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
    hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
    hAge = GetDlgItem(hwnd, IDC_AGE);
    hName = GetDlgItem(hwnd, IDC_NAME);
    mainhwnd = hwnd;
    return TRUE;
}

void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDC_BUTTON1)
    {
        int lenght1 = GetWindowTextLength(hEdit1);
        int lenght2 = GetWindowTextLength(hEdit3);
        int lenght3 = GetWindowTextLength(hName);
        int lenght4 = GetWindowTextLength(hAge);
        if (!lenght1 || !lenght2 || !lenght3 || !lenght4)
        {
            MessageBox(hwnd, L"Не все поля заполнены!", L"Ошибка", 0);
        }
        else
        {
            hookFlag = 1;
            wofstream dataBase("database.txt", ios::out | ios::trunc);
            if (dataBase.is_open()) {
                dataBase << "";
                TCHAR Login[30], Password[30];
                GetWindowText(hEdit1, Login, 30);
                GetWindowText(hEdit3, Password, 30);
                dataBase << Login << endl;
                dataBase << Password << endl;
                dataBase.close();
            }
            MessageBox(hwnd, L"Регистрация успешна", L"Успешно", 0);
            EndDialog(hwnd, 0);
        }
    }
}

BOOL CALLBACK CAdditionalModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
         