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
		mMap = new GameMap(ID_MAP_CHARLESTON, L"Resources\\Map\\Chaleston_Map.png", L"Resources\\Map\\Matrix_Chaleston_Map.txt"/*,Truyen Grid*/);
		break;
	case ID_MAP_CHARLESTON_BOSS_LIGHT:
		mMap = new GameMap(ID_MAP_CHARLESTON_BOSS_LIGHT, L"Resources\\Map\\Chaleston_MapBoss.png", L"Resources\\Map\\Matrix_Chaleston_MapBoss.txt");
		break;
	case ID_MAP_PITTSBURGH_DARK:
		mMap = new GameMap(ID_MAP_PITTSBURGH_DARK, L"Resources\\Map\\Pittsburgh_Dark_Map.png", L"Resources\\Map\\Matrix_Pittsburgh_Dark_Map.txt");
		break;
	case ID_MAP_PITTSBURGH_DARK_EXTRA_1:
		mMap = new GameMap(ID_MAP_PITTSBURGH_DARK_EXTRA_1, L"Resources\\Map\\pittsburgh_dark_extramap1.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap1.txt");
		break;
	case ID_MAP_PITTSBURGH_DARK_EXTRA_2:
		mMap = new GameMap(ID_MAP_PITTSBURGH_DARK_EXTRA_2, L"Resources\\Map\\pittsburgh_dark_extramap2.png", L"Resources\\Map\\Matrix_pittsburgh_dark_extramap2.txt");
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
	int gridColNum = (int)ceil(mMap->GetWidth() / gridCellSize);
	int gridRowNum = (int)ceil(mMap->GetHeight() / gridCellSize);
	mGrid = new Grid(gridColNum, gridRowNum, gridCellSize);

	
	mPlayer = new Player();
	mPlayer->SetPosition(mMap->GetPlayerSpawnPoint());
	mGrid->Add(mPlayer);

	// Setup Enemies
	Enemy* enemy = nullptr;
	// -----GunEnemy-----
	enemy = new GunEnemy();
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	enemy = new GunEnemy(D3DXVECTOR3(688.0f, 338.0f, 0.f));
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	/*gunEnemy3 = new GunEnemy(D3DXVECTOR3(776.0f, 416.0f, 0.f));*/
	enemy = new GunEnemy(D3DXVECTOR3(944.0f, 338.0f, 0.f));
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	// ------------------

	// -----MissileEnemy-----
	enemy = new MissileEnemy(D3DXVECTOR3(344.0f, 416.0f, 0.f), 1);
	enemy = new MissileEnemy(D3DXVECTOR3(1568.0f, 416.0f, 0.f), 2);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	// ----------------------

	// -----RunEnemy-----
	enemy = new RunEnemy();
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	// ------------------

	//------Ground-------
	ground1 = new Ground(D3DXVECTOR3(0,444,0));
	ground2 = new Ground(D3DXVECTOR3(16, 444, 0));
	ground3 = new Ground(D3DXVECTOR3(32, 444, 0));
	ground4 = new Ground(D3DXVECTOR3(48, 444, 0));
	ground5 = new Ground(D3DXVECTOR3(64, 444, 0));
	ground6 = new Ground(D3DXVECTOR3(80, 444, 0));
	ground7 = new Ground(D3DXVECTOR3(96, 444, 0));
	ground8 = new Ground(D3DXVECTOR3(112, 444, 0));
	ground9 = new Ground(D3DXVECTOR3(128, 444, 0));
	ground10 = new Ground(D3DXVECTOR3(144, 444, 0));

	//----------------
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

	for (int i = 0; i < mEnemies.size(); ++i)
	{
		//mEnemies[i]->GetEnemyType()
		mEnemies[i]->Update(deltaTime, mPlayer);
	}

	CheckCamera();
	CheckChageMap();
}

void DemoScene::Draw()
{
	mMap->Draw();
	mPlayer->Draw();

	D3DXVECTOR2 trans = D3DXVECTOR2(Game::GetInstance().GetWidth() / 2 - mCamera->GetPosition().x, Game::GetInstance().GetHeight() / 2 - mCamera->GetPosition().y);

	for (int i = 0; i < mEnemies.size(); ++i)
	{
		mEnemies[i]->Draw(trans);
	}

	// -----Ground-----
	ground1->Draw(trans);
	ground2->Draw(trans);
	ground3->Draw(trans);
	ground4->Draw(trans);
	ground5->Draw(trans);
	ground6->Draw(trans);
	ground7->Draw(trans);
	ground8->Draw(trans);
	ground9->Draw(trans);
	ground10->Draw(trans);
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
