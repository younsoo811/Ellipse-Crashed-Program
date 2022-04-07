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
		620,
		480,
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
	static int v;
	static bool isMove;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rectView);
		x = 20; y = 20;
		v = 0;
		isMove = false;	
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Ellipse(hdc, x - 20, y - 20, x + 20, y + 20);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN){
			if (!isMove){	
				isMove = true;
				SetTimer(hwnd, 1, 500, NULL);
			}
			else {
				isMove = false;
				v = 0;	
				KillTimer(hwnd, 1);	
			}
		}

		if (isMove){
			if (wParam == VK_RIGHT) v = 1;
			if (wParam == VK_LEFT) v = 2;
			if (wParam == VK_DOWN) v = 3;
			if (wParam == VK_UP) v = 4;
		}
		if (wParam == VK_RIGHT) SetTimer(hwnd, 1, 500, NULL);
		break;
	case WM_TIMER:
		if (v == 1) {
			if (x + 40 > rectView.right) {	//원이 윈도우 모서리에 접촉하면 그 자리에서 멈춥니다. (다시 엔터를 눌러야 방향키가 작동합니다.)
				isMove = false;
				v = 0;
				KillTimer(hwnd, 1);
			}
			else x += 40;
		}
		else if (v == 2) {
			if (x - 40 < rectView.left) {
				isMove = false;
				v = 0;
				KillTimer(hwnd, 1);
			}
			else x -= 40;
		}
		else if (v == 3) {
			if (y + 40 > rectView.bottom) {
				isMove = false;
				v = 0;
				KillTimer(hwnd, 1);
			}
			else y += 40;
		}
		else if (v == 4) {
			if (y - 40 < rectView.top) {
				isMove = false;
				v = 0;
				KillTimer(hwnd, 1);
			}
			else y -= 40;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}