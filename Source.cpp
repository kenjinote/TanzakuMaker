#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton;
	static HWND hEdit1;
	static HWND hEdit2;
	switch (msg)
	{
	case WM_CREATE:
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("織姫と彦星が逢えますように。"), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("短冊に変換"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hEdit1, 10, 10, 512, 32, TRUE);
		MoveWindow(hButton, 10, 50, 256, 32, TRUE);
		MoveWindow(hEdit2, 10, 90, 64, 512, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			TCHAR szText[1024];
			GetWindowText(hEdit1, szText, 1024);
			const int nLength = lstrlen(szText);
			TCHAR szChar[2] = { 0 };
			SetWindowText(hEdit2, 0);
			SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("★┷┓\r\n"));
			const WORD ja_JP = MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN);
			for (int i = 0; i < nLength; ++i)
			{
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("┃"));
				szChar[0] = szText[i];
				const int nLen = LCMapStringW(ja_JP, LCMAP_FULLWIDTH, szChar, -1, NULL, 0);
				LPWSTR szWChar = (LPWSTR)GlobalAlloc(0, sizeof(WCHAR) * nLen);
				LCMapStringW(ja_JP, LCMAP_FULLWIDTH, szChar, -1, szWChar, nLen);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)szWChar);
				GlobalFree(szWChar);
				SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("┃\r\n"));
			}
			SendMessage(hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("┗━★\r\n"));
			SetFocus(hEdit2);
			SendMessage(hEdit2, EM_SETSEL, 0, -1);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("短冊メーカー"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
