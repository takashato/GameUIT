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

	gunEnemy1 = new GunEnemy();
	gunEnemy2 = new GunEnemy(D3DXVECTOR3(688.0f, 338.0f, 0.f));
	gunEnemy3 = new GunEnemy(D3DXVECTOR3(776.0f, 416.0f, 0.f));
	gunEnemy4 = new GunEnemy(D3DXVECTOR3(944.0f, 338.0f, 0.f));

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

	gunEnemy1->Update(deltaTime, mPlayer);
	gunEnemy2->Update(deltaTime, mPlayer);
	gunEnemy3->Update(deltaTime, mPlayer);
	gunEnemy4->Update(deltaTime, mPlayer);

	CheckCamera();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();

	D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x, Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);
	gunEnemy1->Draw(trans);
	gunEnemy2->Draw(trans);
	gunEnemy3->Draw(trans);
	gunEnemy4->Draw(trans);

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