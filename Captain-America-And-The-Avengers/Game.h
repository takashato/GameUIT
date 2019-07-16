#pragma once
#include "Window.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Animation.h"

class Game : ISingleton {
private:
	LPDIRECT3D9	d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;
	LPD3DXLINE lineDraw = NULL;
	LPD3DXFONT fontDraw = NULL;

	Window& wnd = Window::GetInstance();
	Timer& timer = Timer::GetInstance();

public:
	static Game& GetInstance();
	void Init();
	void Run();
	~Game();
	LPD3DXSPRITE GetSpriteHandler();

	int GetWidth();
	int GetHeight();

private:
	Game() : ISingleton(NULL) {};

	void InitDevice();
	void Update();
	void Render();
};