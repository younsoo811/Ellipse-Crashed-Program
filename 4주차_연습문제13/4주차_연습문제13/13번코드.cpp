#include <windows.h>
#include <TCHAR.H>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);
	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		650,
		500,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;
	static int  x, y;
	static RECT rectView;
	static int maxh, maxw;
	static bool flag;
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		x = 20; y = 20;
		maxh = (rectView.bottom / 40) * 40;
		maxw = (rectView.right / 40) * 40;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		Rectangle(hdc, 0, 0, maxw, maxh);
		if (flag)
			SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYUP:
		flag = false;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RIGHT) {
			if (x + 40 > maxw) {
				flag = true;
			}
			else x += 40;
		}
		else if (wParam == VK_LEFT) {
			if (x - 40 < 0) {
				flag = true;
			}
			else x -= 40;
		}
		else if (wParam == VK_UP) {
			if (y - 40 < 0) {
				flag = true;
			}
			else y -= 40;
		}
		else if (wParam == VK_DOWN) {
			if (y + 40 > maxh) {
				flag = true;
			}
			else y += 40;
		}

		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}