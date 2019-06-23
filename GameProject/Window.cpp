#include "pch.h"
#include "Window.h"

Window& Window::GetInstance()
{
	static Window instance;
	return instance;
}

void Window::Init(int nShowCmd)
{
#ifdef SHOW_CONSOLE
	InitConsole();
#endif

	hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = WIN_CLASS_NAME;
	wc.hInstance = hInstance;
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

	hWnd = CreateWindow(
		WIN_CLASS_NAME,
		WIN_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == nullptr) ThrowGameException("Can't create game window.");

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

#ifdef SHOW_CONSOLE
void Window::InitConsole()
{
	AllocConsole();
	freopen_s((FILE * *)stdout, "CONOUT$", "w", stdout);
	std::cout << "Game Debug Console allocated." << std::endl;
}
#endif

bool Window::ProcessMessage() const
{
	static MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
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

const std::tuple<UINT, UINT> Window::GetDimension()
{
	RECT rect;
	if (GetWindowRect(hWnd, &rect))
	{
		return { rect.right - rect.left, rect.bottom - rect.top };
	}
	return { 0, 0 };
}

const UINT Window::GetHeight()
{
	auto [width, height] = GetDimension();
	return height;
}

const UINT Window::GetWidth()
{
	auto [width, height] = GetDimension();
	return height;
}
