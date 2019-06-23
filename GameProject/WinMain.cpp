#include "pch.h"
#include "Window.h"
#include "Game.h"

int WINAPI WinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	Window::GetInstance().Init(nShowCmd);
	Game::GetInstance().Init();

	Game::GetInstance().Run();
}