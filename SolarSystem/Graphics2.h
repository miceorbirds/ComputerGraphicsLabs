#include <windows.h>
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma once

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue);
	void DrawIndexed(UINT count);
	void SetProjection(DirectX::FXMMATRIX proj);

	DirectX::XMMATRIX GetProjection();
private:
	DirectX::XMMATRIX projection;

	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};