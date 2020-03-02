#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <Windows.h>
#include <iostream>
#include "winuser.h"
#include <wrl.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")


using namespace DirectX;



class ModelClass
{
private:

	struct DataOffset
	{
		float x, y;
	};
	struct Vertex {
		float x, y, z;
		float r,g,b,a;
	};

public:
	ModelClass();
	ModelClass(float, float);
	ModelClass(float, float, float, float);
	ModelClass(const ModelClass&);
	~ModelClass();

	virtual void ResetPosition();
	virtual void UpdatePositionByDirection();
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(ID3D11DeviceContext*, ID3D11Device*);

	int GetIndexCount();

public:
	DataOffset pData;
	float currentLocation[2];
	float direction[2];

private:
	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*, ID3D11Device*);

protected:

	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer, * m_colorBuffer, * m_positionBuffer, * m_constBuffer;
	int m_vertexCount, m_indexCount;
	Vertex vertices[4] = {};


};