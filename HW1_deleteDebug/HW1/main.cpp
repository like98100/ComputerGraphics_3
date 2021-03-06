#include <windows.h>

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE
	hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;
	wc.style = 0;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MyWndClass";
	RegisterClass(&wc);
	hwnd = CreateWindow(
		"MyWndClass", // WNDCLASS name
		"SDK Application", // Window title
		WS_OVERLAPPEDWINDOW, // Window style
		CW_USEDEFAULT, // Horizontal position
		CW_USEDEFAULT, // Vertical position
		1000, // Initial width
		800, // Initial height
		HWND_DESKTOP, // Handle of parent window
		NULL, // Menu handle
		hInstance, // Application's instance handle
		NULL // Window-creation data
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	Shape* shapes[5] = { NULL };
	shapes[0] = new _Circle(100, 100, 50);
	shapes[1] = new _Rectangle(300, 300, 100, 100);
	shapes[2] = new _Rectangle(200, 100, 50, 150);
	shapes[3] = new _Circle(100, 300, 150);
	shapes[4] = new _Rectangle(200, 200, 200, 200);
	RECT rects[5];
	for (int i = 0; i < 5; i++)
		rects[i] = RECT{ (LONG)shapes[i]->_x, (LONG)shapes[i]->_y,
		(LONG)shapes[i]->_x + 500, (LONG)shapes[i]->_y + 50 };

	rects[1] = RECT{ (LONG)shapes[1]->_x, (LONG)shapes[1]->_y + 50, (LONG)shapes[1]->_x + 500, (LONG)shapes[1]->_y + 100 };
	rects[2] = RECT{ (LONG)shapes[2]->_x, (LONG)shapes[2]->_y + 50, (LONG)shapes[2]->_x + 500, (LONG)shapes[2]->_y + 100 };

	//rects[0] = RECT{ (LONG)shapes[0]->_x, (LONG)shapes[0]->_y, (LONG)shapes[0]->_x + 200, (LONG)shapes[0]->_y +50 };
	//rects[1] = RECT{ (LONG)shapes[1]->_x, (LONG)shapes[1]->_y, (LONG)shapes[1]->_x + 200, (LONG)shapes[1]->_y + 50 };
	//rects[2] = RECT{ (LONG)shapes[2]->_x, (LONG)shapes[2]->_y, (LONG)shapes[2]->_x + 200, (LONG)shapes[2]->_y + 50 };
	//rects[3] = RECT{ (LONG)shapes[3]->_x, (LONG)shapes[3]->_y, (LONG)shapes[3]->_x + 200, (LONG)shapes[3]->_y + 50 };
	//rects[4] = RECT{ (LONG)shapes[4]->_x, (LONG)shapes[4]->_y, (LONG)shapes[4]->_x + 200, (LONG)shapes[4]->_y + 50 };
	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//Ellipse(hdc, 0, 0, 200, 100);

		RECT rect;
		GetClientRect(hwnd, &rect);
		//DrawText(hdc, "hello, Windows", -1, &rect,
		//	DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		for (int i = 0; i < 5; ++i)
			shapes[i]->Draw(hdc, rects[i]);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		for (int i = 0; i < 5; ++i)
		{
			delete shapes[i];
			shapes[i] = NULL;
		}
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}