#pragma once
#include <Windows.h>
#include <iostream>
#include "winuser.h"
#include <wrl.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <DirectXColors.h>
#include <dcomp.h>
using namespace DirectX;


class D3DSetup
{
public:
	struct Vertex
	{
		Vertex(float x, float y)
			: pos(x, y) {}

		XMFLOAT2 pos;
	};

	D3DSetup();
	D3DSetup(const D3DSetup& D3DSetup);

	~D3DSetup();

	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd,
		float screenDepth, float screenNear);
	void Release();

	void BeginScene(float r, float g, float b, float a);
	void BeginScene(XMVECTORF32);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX& projectionMatrix);
	void GetWorldMatrix(XMMATRIX& worldMatrix);
	void GetOrthoMatrix(XMMATRIX& orthoMatrix);

	void GetVideoCardInfo(char* cardName, int& memory);


private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
	bool Init();

};



