#include "Game.h"
#include "GameGlobal.h"
#include "../GameControllers/SceneManager.h"
#include "../Scenes/DemoScene.h"

Game::Game(int fps)
{
	mFPS = fps;

	SceneManager::GetInstance()->ReplaceScene(new DemoScene());

	InitLoop();
}

Game::~Game()
{

}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);

	Render();
}

void Game::Render()
{
	auto device = GameGlobal::GetCurrentDevice();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackcolor(), 0.0f, 0);

	{
		device->BeginScene();

		//bat dau ve
		GameGlobal::GetCurrentSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

		//draw here
		scene->Draw();

		//ket thuc ve
		GameGlobal::GetCurrentSpriteHandler()->End();

		device->EndScene();
	}

	device->Present(0, 0, 0, 0);
}

void Game::InitLoop()
{
	MSG msg;

	float tickPerFrame = 1.0f / mFPS, delta = 0;

	while (GameGlobal::isGameRunning)
	{
		GameTime::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += GameTime::GetInstance()->GetCouter();

		if (delta >= tickPerFrame)
		{
			Update((delta));
			delta = 0;
		}
		else
		{
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
}