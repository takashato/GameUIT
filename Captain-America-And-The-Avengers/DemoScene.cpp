#include "pch.h"
#include "Game.h"
#include "DemoScene.h"

DemoScene::DemoScene() : Scene()
{
	MapID = 0;
	MapMaxID = 6;
	Setup();
}

DemoScene::~DemoScene()
{
	delete mCamera;
}

void DemoScene::Setup()
{
	Scene::Setup();

	//Setup Map
	switch (MapID)
	{
	case ID_MAP_CHARLESTON:
		mMap = new GameMap(ID_MAP_CHARLESTON, L"Resources\\Map\\Chaleston_Map.png", L"Resources\\Map\\Matrix_Chaleston_Map.txt");
		break;
	case ID_MAP_CHARLESTON_BOSS_LIGHT:
		mMap = new GameMap(ID_MAP_CHARLESTON_BOSS_LIGHT, L"Resources\\Map\\Chaleston_MapBoss.png", L"Resources\\Map\\Matrix_Chaleston_MapBoss.txt");
		break;
	case ID_MAP_PITTSBURGH_DARK:
		mMap = new GameMap(ID_MAP_PITTSBURGH_DARK, L"Resources\\Map\\Pittsburgh_Dark_Map.png", L"Resources\\Map\\Matrix_Pittsburgh_Dark_Map.txt");
		break;
	case ID_MAP_PITTSBURGH_EXTRA_1:
		mMap = new GameMap(ID_MAP_PITTSBURGH_EXTRA_1, L"Resources\\Map\\pittsburgh_dark_extramap1.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap1.txt");
		break;
	case ID_MAP_PITTSBURGH_EXTRA_2:
		mMap = new GameMap(ID_MAP_PITTSBURGH_EXTRA_2, L"Resources\\Map\\pittsburgh_dark_extramap2.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap2.txt");
		break;
	case ID_MAP_RED_ALERT:
		mMap = new GameMap(ID_MAP_RED_ALERT, L"Resources\\Map\\map_red-alert.png", L"Resources\\Map\\Matrix_map_red-alert.txt");
		break;
	default:
		break;
	}
	// Setup Grid
	int gridCellSize = Game::GetInstance().GetWidth() > Game::GetInstance().GetHeight() ?
		Game::GetInstance().GetWidth() 
		: Game::GetInstance().GetHeight();
	int gridColNum = ceil(mMap->GetWidth() / gridCellSize);
	int gridRowNum = ceil(mMap->GetHeight() / gridCellSize);
	mGrid = new Grid(gridColNum, gridRowNum, gridCellSize);

	mPlayer = new Player();
	mPlayer->SetPosition(mMap->GetPlayerSpawnPoint());

	// -----GunEnemy-----
	gunEnemy1 = new GunEnemy();
	gunEnemy2 = new GunEnemy(D3DXVECTOR3(688.0f, 338.0f, 0.f));
	/*gunEnemy3 = new GunEnemy(D3DXVECTOR3(776.0f, 416.0f, 0.f));*/
	gunEnemy4 = new GunEnemy(D3DXVECTOR3(944.0f, 338.0f, 0.f));
	// ------------------

	// -----MissileEnemy-----
	missileEnemy1 = new MissileEnemy();
	missileEnemy2 = new MissileEnemy(D3DXVECTOR3(1568.0f, 416.0f, 0.f));
	// ----------------------

	// -----RunEnemy-----
	runEnemy1 = new RunEnemy();
	// ------------------

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

	// -----GunEnemy-----
	gunEnemy1->Update(deltaTime, mPlayer);
	gunEnemy2->Update(deltaTime, mPlayer);
	/*gunEnemy3->Update(deltaTime, mPlayer);*/
	gunEnemy4->Update(deltaTime, mPlayer);
	// ------------------

	// -----MissileEnemy-----
	missileEnemy1->Update(deltaTime, mPlayer, 1);
	missileEnemy2->Update(deltaTime, mPlayer, 2);
	// ----------------------

	// -----RunEnemy-----
	runEnemy1->Update(deltaTime, mPlayer, EntityDirection::Right);
	// ------------------

	CheckCamera();
	CheckChageMap();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();

	D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x, Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);

	// -----GunEnemy-----
	gunEnemy1->Draw(trans);
	gunEnemy2->Draw(trans);
	/*gunEnemy3->Draw(trans);*/
	gunEnemy4->Draw(trans);
	// ------------------

	// -----MissileEnemy-----
	missileEnemy1->Draw(trans);
	missileEnemy2->Draw(trans);
	// ----------------------

	// -----RunEnemy-----
	runEnemy1->Draw(trans);
	// ------------------

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

void DemoScene::ChangeMap(int ID)
{
	MapID = ID;
	Setup();
}
void DemoScene::CheckChageMap()//Demo
{
	if (MapID == ID_MAP_CHARLESTON)
	{
		if (mPlayer->GetPosition().x >= EXIT_CHARLESTON)
			this->ChangeMap(ID_MAP_CHARLESTON_BOSS_LIGHT);
		
	}
	else if (MapID == ID_MAP_CHARLESTON_BOSS_LIGHT)
	{
		if (mPlayer->GetPosition().x >= DEMO_EXIT_MINIMAP)
			this->ChangeMap(ID_MAP_PITTSBURGH_DARK);
	}
}
