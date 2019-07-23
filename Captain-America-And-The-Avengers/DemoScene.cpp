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
	mMap = new GameMap(L"Resources\\Map\\Chaleston_Map.png",L"Resources\\Map\\Matrix_Chaleston_Map.txt");
	/*mMap = new GameMap(L"Resources\\Map\\Chaleston_MapBoss.png", L"Resources\\Map\\Matrix_Chaleston_MapBoss.txt");*/
	/*mMap = new GameMap(L"Resources\\Map\\Pittsburgh_Dark_Map.png", L"Resources\\Map\\Matrix_Pittsburgh_Dark_Map.txt");*/
	/*mMap = new GameMap(L"Resources\\Map\\pittsburgh_dark_extramap1.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap1.txt");*/
	/*mMap = new GameMap(L"Resources\\Map\\pittsburgh_dark_extramap2.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap2.txt"); */
	/*mMap = new GameMap(L"Resources\\Map\\map_red-alert.png", L"Resources\\Map\\Matrix_map_red-alert.txt");*/
	mPlayer = new Player();
	/*mPlayer->SetPosition(mMap->GetPlayerSpawnPoint());*/

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