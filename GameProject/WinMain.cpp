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
#ifdef DEBUG
	Window::GetInstance().Init(nShowCmd);
	Game::GetInstance().Init();

	Game::GetInstance().Run();
#else
	try {
		Window::GetInstance().Init(nShowCmd);
		Game::GetInstance().Init();

		Game::GetInstance().Run();
	} 
	catch (GameException exception) 
	{
		MessageBoxA(NULL, exception.what(), "ERROR", MB_OK | MB_ERR_INVALID_CHARS);
	}
	catch (...) 
	{
		MessageBoxA(NULL, "Unknown Error.", "ERROR", MB_OK | MB_ERR_INVALID_CHARS);
	}
#endif
}