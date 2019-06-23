#pragma once
class Window : ISingleton
{
private:
	HINSTANCE	m_hInstance = nullptr;
	HWND		m_hWnd = nullptr;

public:
	static Window& GetInstance();
	void Init(int nShowCmd);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	Window() : ISingleton(NULL) {};
};