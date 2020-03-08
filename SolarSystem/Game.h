#include <windows.h>
#include <memory>
#include "Window.h"
#pragma once

class Game
{
public:
	Game(int clientAreaWidth, int clientAreaHeight, const wchar_t* appName);

	// master frame / message loop
	int Go();
	~Game();

	HRESULT InitDevice();
	HRESULT InitGeometry();
	HRESULT InitMatrixes();
	void SetMatrixes(float fAngle);
	void Render();


	void CleanupDevice();


private:
	int DoFrame();
private:
	Window wnd;
	int width;
	int height;
	const wchar_t* appName;



	HINSTANCE               g_hInst = nullptr;
	HWND                    g_hWnd = nullptr;

	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*			g_pd3dDevice = nullptr;		// Устройство (для создания объектов)
	ID3D11DeviceContext*	g_pImmediateContext = nullptr;	// Контекст (устройство рисования)
	IDXGISwapChain*			g_pSwapChain = nullptr;		// Цепь связи (буфера с экраном)
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;	// Объект вида, задний буфер
	ID3D11Texture2D*		g_pDepthStencil = nullptr;		// Текстура буфера глубин
	ID3D11DepthStencilView* g_pDepthStencilView = nullptr;	// Объект вида, буфер глубин

	ID3D11VertexShader*		g_pVertexShader = nullptr;		// Вершинный шейдер
	ID3D11PixelShader*		g_pPixelShader = nullptr;		// Пиксельный шейдер
	ID3D11InputLayout*		g_pVertexLayout = nullptr;		// Описание формата вершин
	ID3D11Buffer*			g_pVertexBuffer = nullptr;		// Буфер вершин
	ID3D11Buffer*			g_pIndexBuffer = nullptr;		// Буфер индексов вершин
	ID3D11Buffer*			g_pConstantBuffer = nullptr;	// Константный буфер

	XMMATRIX                g_World;					// Матрица мира
	XMMATRIX                g_View;						// Матрица вида
	XMMATRIX                g_Projection;				// Матрица
};