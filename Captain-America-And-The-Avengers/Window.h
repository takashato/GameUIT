#pragma once
#include "SceneManager.h"

class Window : ISingleton
{
private:
	HINSTANCE hInstance = nullptr;
	HWND hWnd = nullptr;

public:
	static Window& GetInstance();	
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Init(int nShowCmd);
#ifdef SHOW_CONSOLE
	void InitConsole();
#endif
	bool ProcessMessage() const;

	const HWND GetHWnd() const { return hWnd; }
	const HINSTANCE GetHInstance() const { return hInstance;  };
	
	const std::tuple<UINT, UINT> GetDimension();
	const UINT GetHeight();
	const UINT GetWidth();

	void SetTitle(std::wstring str);

private:
	Window() : ISingleton(NULL) {};
};