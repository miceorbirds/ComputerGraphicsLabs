#include "Graphics.h"
#include "ModelClass.h"

Graphics::Graphics() {};

Graphics::Graphics(const Graphics& graphics) {};

Graphics::~Graphics()
{
	Release();
}

void Graphics::Release()
{
	if (m_direct)
	{
		m_direct->Release();
		m_direct.reset();
		m_direct = nullptr;
	}
}

bool Graphics::DoFrame()
{
	return Render();
}

void Graphics::updateOffset(int player, float x, float y)
{
	if (player == 0)
	{
		m_leftPaddle->updatePositionByClick(x, y);
	}
	if (player == 1)
	{
		m_rightPaddle->updatePositionByClick(x, y);
	}

}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_direct = std::make_unique<D3DSetup>();
	if (!m_direct)
	{
		return false;
	}

	bool result = m_direct->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, L"DirectX initial failed", L"Error", MB_OK);
		return result;
	}
	else
	{
		result = Init();
	}
	m_ball = std::make_unique<Ball>(0.55, 1);
	if (!m_ball)
	{
		return false;
	}
	m_leftPaddle = std::make_unique<Paddle>(-0.97);
	result = m_leftPaddle->Initialize(m_direct->GetDevice(), m_direct->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_rightPaddle = std::make_unique<Paddle>(0.97);
	result = m_rightPaddle->Initialize(m_direct->GetDevice(), m_direct->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the model object.
	result = m_ball->Initialize(m_direct->GetDevice(), m_direct->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_ShaderClass = std::make_unique<ShaderClass>();

	bool res = m_ShaderClass->Initialize(m_direct->GetDevice(), m_direct->GetDeviceContext(), hwnd);

	return result;
}

bool Graphics::Render()
{
	static int leftScore = 0;
	static int rightScore = 0;

	bool result;
	m_direct->BeginScene(DirectX::Colors::SeaGreen);

	if (std::abs(m_ball->getPositionX()) >= 0.95)
	{
		if (m_ball->getPositionX() < 0)
		{
			if ((m_ball->getPositionY() > m_leftPaddle->currentLocation[1] + 0.15) || (m_ball->getPositionY() < m_leftPaddle->currentLocation[1] - 0.15)) {
				rightScore++;
				m_ball->ResetPosition();
				std::cout << "rightScore: " << rightScore << std::endl;
			}
		}
		else
		{
			if ((m_ball->getPositionY() > m_rightPaddle->currentLocation[1] + 0.15) || (m_ball->getPositionY() < m_rightPaddle->currentLocation[1] - 0.15)) {
				leftScore++;
				m_ball->ResetPosition();
				std::cout << "leftScore: " << leftScore << std::endl;
			}
		}

	}

	m_ball->Render(m_direct->GetDeviceContext(), m_direct->GetDevice());
	m_leftPaddle->Render(m_direct->GetDeviceContext(), m_direct->GetDevice());
	m_rightPaddle->Render(m_direct->GetDeviceContext(), m_direct->GetDevice());

	m_direct->EndScene();

	return true;
}

bool Graphics::Init()
{
	backgroundColor = std::make_unique<XMVECTORF32>(DirectX::Colors::DarkMagenta);
	return true;
}


