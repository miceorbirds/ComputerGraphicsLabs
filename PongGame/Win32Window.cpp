#include "Win32Window.h"

Window::Window(int width, int height, const wchar_t* name)
	: clientAreaWidth(width), clientAreaHeight(height), m_appName(name)
{
}
Window::Window(const Window& app)
{
}
Window::~Window()
{
	Release();
}

bool Window::Initialize()
{
	InitializeWindow();
	m_input = std::make_unique<Input>();
	if (m_input)
	{
		m_input->Initialize();
	}
	else
	{
		return false;
	}

	m_graphics = std::make_unique<Graphics>();
	if (m_graphics)
	{
		m_graphics->Initialize(clientAreaWidth, clientAreaHeight, m_hWnd);
	}
	else
	{
		return false;
	}

	return true;
}

void Window::Run()
{
	MSG msg;
	bool result;

	ZeroMemory(&msg, sizeof(MSG));
	exitApp = false;

	while (!exitApp)
	{
		if (PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == (WM_QUIT || WM_CLOSE))
		{
			exitApp = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = DoFrame();
			if (!result)
			{
				exitApp = true;
			}
		}
	}
}

void Window::Release()
{
	// Release the graphics object.
	if (m_graphics)
	{
		m_graphics->Release();
		m_graphics = nullptr;
	}

	// Release the input object.
	if (m_input)
	{
		m_input = nullptr;
	}

	// Shutdown the window.
	ReleaseWindow();

	return;

}

bool Window::DoFrame()
{
	if (m_input->IsKeyPressed(VK_ESCAPE))
	{
		return false;
	}
	if (m_input->IsKeyPressed(87)) m_graphics->updateOffset(0, 0, 0.015);
	if (m_input->IsKeyPressed(83)) m_graphics->updateOffset(0, 0, -0.015);
	if (m_input->IsKeyPressed(38)) m_graphics->updateOffset(1, 0, 0.015);
	if (m_input->IsKeyPressed(40)) m_graphics->updateOffset(1, 0, -0.015);

	return m_graphics->DoFrame();
}

void Window::InitializeWindow()
{
	WNDCLASSEX wc = { 0 };

	ApplicationHandle = this;

	m_hInstance = GetModuleHandle(nullptr);

	/// Setup the windows class with default settings.
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_appName;
	wc.cbSize = sizeof(wc);

	// Register the window class.
	RegisterClassEx(&wc);

	// calculate window size based on desired client region size
	RECT windowRect;
	windowRect.left = 100;
	windowRect.right = clientAreaWidth + windowRect.left;
	windowRect.top = 100;
	windowRect.bottom = clientAreaHeight + windowRect.top;
	AdjustWindowRect(&windowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	// Create the window with the screen settings and get the handle to it.
	m_hWnd = CreateWindow(
		m_appName,
		m_appName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		nullptr, nullptr,
		m_hInstance, this);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);
}

void Window::ReleaseWindow()
{
	// Remove the window.
	DestroyWindow(m_hWnd);
	m_hWnd = nullptr;
	// Remove the application instance.
	UnregisterClass(m_appName, m_hInstance);
	m_hInstance = nullptr;
	// Release the pointer to this class.
	ApplicationHandle = nullptr;
	return;
}

LRESULT Window::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			m_input->KeyDown((unsigned int)wParam);
			return 0;
		}
		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			m_input->KeyUp((unsigned int)wParam);
			return 0;
		}

		case WM_PAINT:
		{
			const bool isCorrect = DoFrame();
			if (!isCorrect)
			{
				exitApp = true;
			}
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ApplicationHandle->MessageHandler(hWnd, uMsg, wParam, lParam);
}

