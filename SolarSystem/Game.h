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
	ID3D11Device*			g_pd3dDevice = nullptr;		// ���������� (��� �������� ��������)
	ID3D11DeviceContext*	g_pImmediateContext = nullptr;	// �������� (���������� ���������)
	IDXGISwapChain*			g_pSwapChain = nullptr;		// ���� ����� (������ � �������)
	ID3D11RenderTargetView* g_pRenderTargetView = nullptr;	// ������ ����, ������ �����
	ID3D11Texture2D*		g_pDepthStencil = nullptr;		// �������� ������ ������
	ID3D11DepthStencilView* g_pDepthStencilView = nullptr;	// ������ ����, ����� ������

	ID3D11VertexShader*		g_pVertexShader = nullptr;		// ��������� ������
	ID3D11PixelShader*		g_pPixelShader = nullptr;		// ���������� ������
	ID3D11InputLayout*		g_pVertexLayout = nullptr;		// �������� ������� ������
	ID3D11Buffer*			g_pVertexBuffer = nullptr;		// ����� ������
	ID3D11Buffer*			g_pIndexBuffer = nullptr;		// ����� �������� ������
	ID3D11Buffer*			g_pConstantBuffer = nullptr;	// ����������� �����

	XMMATRIX                g_World;					// ������� ����
	XMMATRIX                g_View;						// ������� ����
	XMMATRIX                g_Projection;				// �������
};