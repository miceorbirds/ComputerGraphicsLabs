#include <windows.h>
#include "Game.h"

//--------------------------------------------------------------------------------------
// ����� ����� � ���������. ������������� ���� �������� � ���� � ���� ���������.
// ��������� ����� ������������ ��� ��������� �����.
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdshow)
 
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);
	bool result;

	Game(800, 800, L"Solar System").Go();

	return 0;
}