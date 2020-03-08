#include "Window.h"

Window::Window(int width, int height, const wchar_t* name)
	: width(width), height(height)
{
	// calculate window size based on desired client region size
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	// create window & get hWnd
	hWnd = CreateWindow(
		WindowClass::GetName(),
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	// newly created windows start off as hidden
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	// create graphics object
	pGraphicsObject = std::make_unique<Graphics>(hWnd);
	m_hInst = WindowClass::GetInstance();
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

Graphics& Window::pGraphicsObject()
{
	return *pGfx;
}

//--------------------------------------------------------------------------------------
// ¬ызываетс€ каждый раз, когда приложение получает системное сообщение
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass()
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = wc.hIcon;

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const wchar_t* Window::WindowClass::GetName()
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return wndClass.hInst;
}