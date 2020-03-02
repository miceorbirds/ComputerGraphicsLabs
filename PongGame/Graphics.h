#pragma once
#include <iostream>
#include <Windows.h>
#include "D3D.h"
#include "ShaderClass.h"
#include "ModelClass.h"
#include "Ball.h"
#include "Paddle.h"


using namespace DirectX;
using Microsoft::WRL::ComPtr;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics& graphics);
	~Graphics();

	void Release();

	bool DoFrame();
	void updateOffset(int, float, float);

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

private:
	const bool FULL_SCREEN = false;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

private:
	bool Render();
	bool Init();

private:
	std::unique_ptr<D3DSetup> m_direct;
	std::unique_ptr<Ball> m_ball;
	std::unique_ptr<Paddle> m_leftPaddle;
	std::unique_ptr<Paddle> m_rightPaddle;
	std::unique_ptr<ShaderClass> m_ShaderClass;
	std::unique_ptr <XMVECTORF32> backgroundColor;
};



