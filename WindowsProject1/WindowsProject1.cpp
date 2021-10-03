// WindowsProject1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include <Windows.h>
#include "resource.h"
#include <CommCtrl.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

bool IsEmpty(HWND hEdit)
{
	return GetWindowTextLengthW(hEdit) == 0;
}




INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool error;//良くないやり方

	switch (message) {
	case WM_INITDIALOG:
		SendDlgItemMessageW(hDlg, IDC_EDIT_UserName, EM_SETCUEBANNER, true, LPARAM(L"ユーザー名を入力してください。"));
		return true;

	case WM_CTLCOLOREDIT:
		if (error && GetDlgCtrlID(HWND(lParam)) == IDC_EDIT_UserName) {
			SetBkColor(HDC(wParam), RGB(255, 0, 0));
		}
		return reinterpret_cast<INT_PTR>(GetSysColorBrush(COLOR_WINDOW));
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_EDIT_UserName:
			if (HIWORD(wParam) == EN_UPDATE) {
				const auto hEdit = GetDlgItem(hDlg, IDC_EDIT_UserName);
				if (!IsEmpty(hEdit))
					error = false;
			}
			return true;
		case IDOK:
		{
			const auto hEdit = GetDlgItem(hDlg, IDC_EDIT_UserName);
			if (IsEmpty(hEdit)) {
				error = true;
				SetFocus(hEdit);
			}
			else
				EndDialog(hDlg, IDOK);
		}
			return true;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		default:
			return true;
		}
	default:
		return false;
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG_Login)
	, /*_In_opt_ HWND      hWndParent    */nullptr
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */0
	);
}
