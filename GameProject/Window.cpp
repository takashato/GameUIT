#include "pch.h"
#include "Window.h"

Window& Window::GetInstance()
{
	static Window instance;
	return instance;
}

void Window::Init(int nShowCmd)
{
	m_hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = WIN_CLASS_NAME;
	wc.hInstance = m_hInstance;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	m_hWnd = CreateWindow(
		WIN_CLASS_NAME,
		WIN_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	if (m_hWnd == nullptr) ThrowGameException("Can't create game window.");

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
}

LRESULT Window::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000)) // if key is not holding 
		{
			//SceneManager::Instance().OnKeyDown((BYTE)wParam);
			//Window::Instance().keyStates.set((BYTE)wParam);
		}
		break;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		//SceneManager::Instance().OnKeyUp((BYTE)wParam);
		//Window::Instance().keyStates.reset((BYTE)wParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
