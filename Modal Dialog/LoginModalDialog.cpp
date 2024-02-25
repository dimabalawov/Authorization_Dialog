#include "LoginModalDialog.h"
#include <fstream>
#include <string>
using namespace std;

LoginModalDialog* LoginModalDialog::ptr = NULL;

LoginModalDialog::LoginModalDialog(void)
{
    ptr = this;
}

LoginModalDialog::LoginModalDialog(LPCTSTR lpStr)
{
    ptr = this;
    _tcscpy(text, lpStr);
}

LoginModalDialog::~LoginModalDialog(void)
{

}

void LoginModalDialog::Cls_OnClose(HWND hwnd)
{
    EndDialog(hwnd, IDCANCEL);
}

BOOL LoginModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
    hEdit4 = GetDlgItem(hwnd, IDC_EDIT4);
    return TRUE;
}


void LoginModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDC_BUTTON3)
    {
        wifstream database("database.txt");
        TCHAR Login[30], Password[30];
        int lenght1 = GetWindowTextLength(hEdit2);
        int lenght2 = GetWindowTextLength(hEdit4);
        if (!lenght1 || !lenght2)
        {
            MessageBox(hwnd, L"Не все поля заполнены!", L"Ошибка", 0);
        }
        else
        {
            if (database.is_open()) {
                int i = 0;
                wstring line;
                bool Flag = 0;
                GetWindowText(hEdit2, Login, 30);
                GetWindowText(hEdit4, Password, 30);
                while (getline(database, line))
                {
                    i++;
                    if (i%2!=0)
                    {
                        if (_tcscmp(line.c_str(), Login) == 0)
                            Flag = 1;
                        else
                            Flag = 0;
                    }
                    else
                    {
                        if (_tcscmp(line.c_str(), Password) == 0 && Flag == 1)
                        {
                            MessageBox(hwnd, L"Вход успешен!", L"Успешно", 0);
                            EndDialog(hwnd, 0);
                            database.close();
                            return;
                        }
                    }
                }
                MessageBox(hwnd, L"Неверные данные", L"Ошибка", 0);
                database.close();
            }

        }
    }
}

BOOL CALLBACK LoginModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
    }
    return FALSE;
}

