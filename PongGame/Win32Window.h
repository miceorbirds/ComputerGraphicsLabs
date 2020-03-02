#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h> // win32 
#include <memory> // for unique_ptr
#include "Input.h"
#include "Graphics.h"

class Window
{
private:
	const wchar_t* m_appName;
	int clientAreaWidth, clientAreaHeight;
	HWND m_hWnd;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Graphics> m_graphics;
	HINSTANCE m_hInstance;

public:
	Window(int width, int height, const wchar_t* name);
	Window(const Window& app);
	~Window();
	bool Initialize();
	void Run();
	void Release();

	bool DoFrame();

	void InitializeWindow();
	void ReleaseWindow();

	LRESULT CALLBACK MessageHandler(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	bool exitApp;
};

static LRESULT CALLBACK WndProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

static Window* ApplicationHandle = nullptr;
