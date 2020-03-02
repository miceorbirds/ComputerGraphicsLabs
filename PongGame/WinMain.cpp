#include "Win32Window.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	auto app = std::make_unique<Window>(800,800,L"The pong game");;
	if (!app)
	{
		return 0;
	}
	if(app->Initialize())
	{
		app->Run();
	}
	app->Release();

	return  0;
}
