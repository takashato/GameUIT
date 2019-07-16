#include "pch.h"
#include "Game.h"


void Game::Init()
{
	InitDevice();
}

Game::~Game()
{
	if (backBuffer != NULL) backBuffer->Release();
	if (lineDraw != NULL) lineDraw->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

LPD3DXSPRITE Game::GetSpriteHandler()
{
	return spriteHandler;
}

int Game::GetWidth()
{
	return BUFFER_WIDTH;
}

int Game::GetHeight()
{
	return BUFFER_HEIGHT;
}

void Game::InitDevice()
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	//d3dpp.BackBufferHeight = wnd.GetHeight();
	//d3dpp.BackBufferWidth = wnd.GetWidth();
	d3dpp.BackBufferHeight = BUFFER_HEIGHT;
	d3dpp.BackBufferWidth = BUFFER_WIDTH;

	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		wnd.GetHWnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);
	if (d3ddv == nullptr) ThrowGameException("Can't create DirectX Device.");

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	if (FAILED(D3DXCreateSprite(d3ddv, &spriteHandler)))
		ThrowGameException("Can't create DirectX Device.");
	if (FAILED(D3DXCreateLine(d3ddv, &lineDraw)))
		ThrowGameException("Can't create DirectX Line.");
	if (FAILED(D3DXCreateFontA(d3ddv, 13, 0, FW_NORMAL, 1, //AddFontResourceEx( , , ); if need more custom font
		FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Arial", &fontDraw)))
		ThrowGameException("Can't create DirectX Font.");
}

void Game::Run()
{
	SceneManager::GetInstance().SetupDefaultScene();
	while (wnd.ProcessMessage())
	{
		timer.Update();
		Update();
		Render();
#ifdef SET_TITLE_AS_FPS
		std::wstringstream wss;
		wss.str(L""), wss << WIN_TITLE << " | FPS: " << timer.GetFPS();
		wnd.SetTitle(wss.str());
#endif
	}
}

void Game::Update()
{
	float deltaTime = timer.Get();
	SceneManager::GetInstance().Update(deltaTime);
}

void Game::Render()
{
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, NULL, 0.0f, 0);

	d3ddv->BeginScene();
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	SceneManager::GetInstance().Draw();

	spriteHandler->End();
	d3ddv->EndScene();

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}
