#pragma once
#include <windows.h>
#include <memory>
#include "Graphics2.h"

class Window
{
private:
	// singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const wchar_t* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();
		static constexpr const wchar_t* wndClassName = L"GameWindow";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};

public:
	Window(int width, int height, const wchar_t* name);
	~Window();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	int width;
	int height;
	HWND hWnd;
	HINSTANCE m_hInst;
	std::unique_ptr<Graphics> pGraphicsObject;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);