#include "AdditionalModalDialog.h"
#include <fstream>
using namespace std;

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

}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
    hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
    hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
    hAge = GetDlgItem(hwnd, IDC_AGE);
    hName = GetDlgItem(hwnd, IDC_NAME);
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
         