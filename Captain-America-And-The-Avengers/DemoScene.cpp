#include "pch.h"
#include "Game.h"
#include "DemoScene.h"

DemoScene::DemoScene() : Scene()
{
	Setup();
}

DemoScene::~DemoScene()
{
	delete mCamera;
}

void DemoScene::Setup()
{
	Scene::Setup();
	mMap = new GameMap((char*)"Resources\\Map\\CharlestonMap.tmx");
	mPlayer = new Player();
	mPlayer->SetPosition(mMap->GetPlayerSpawnPoint());

	mCamera = new Camera(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());
	mMap->SetCamera(mCamera);
	mPlayer->SetCamera(mCamera);

	CheckCamera();
}

void DemoScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	mPlayer->HandleKeyboard(SceneManager::GetInstance().GetKeyboard());
	mPlayer->Update(deltaTime);

	CheckCamera();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();
	Scene::Draw();
}

void DemoScene::CheckCamera()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		mCamera->SetPosition(mCamera->GetWidth() / 2, (int)mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			(int)mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		mCamera->SetPosition((int)mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		mCamera->SetPosition((int)mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}