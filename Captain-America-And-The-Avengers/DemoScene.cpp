#include "pch.h"
#include "Game.h"
#include "DemoScene.h"
#include "SoundManager.h"

DemoScene::DemoScene() : Scene("Resources\\Map\\Charleston_Map.xml")
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
	//Setup Map
	switch (MapID)
	{
	case ID_MAP_CHARLESTON:
		mMap = new GameMap(ID_MAP_CHARLESTON, L"Resources\\Map\\Chaleston_Map.png", L"Resources\\Map\\Matrix_Chaleston_Map.txt");
		SoundManager::GetInstance().CLoopSound(ThemeOfCaptainAmerica);
		break;
	case ID_MAP_CHARLESTON_BOSS_LIGHT:
		SoundManager::GetInstance().CStopsound(ThemeOfCaptainAmerica);
		SoundManager::GetInstance().CLoopSound(BossBattle);
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
		Game::GetInstance().GetWidth() / 2
		: Game::GetInstance().GetHeight() / 2;
	int gridColNum = (int)ceil(1.0f * mMap->GetWidth() / gridCellSize);
	int gridRowNum = (int)ceil(1.0f * mMap->GetHeight() / gridCellSize);
	mGrid = new Grid(gridColNum, gridRowNum, gridCellSize);

	// Setup Enemies
	Enemy* enemy = nullptr;

	// Setup map object
	switch (MapID)
	{
	default:
	case ID_MAP_CHARLESTON:
		MapObjectReader::LoadFromFile("Resources\\Map\\CharlestonMapObjects.xml", mGrid);
		break;
	case ID_MAP_CHARLESTON_BOSS_LIGHT:
		MapObjectReader::LoadFromFile("Resources\\Map\\CharlestonBossMapObjects.xml", mGrid);
		//-----Add Boss
		enemy = new BossCharleston(D3DXVECTOR3(189.0f, 145.0f, .0f));
		mEnemies.push_back(enemy);
		mGrid->Add(enemy);
		break;
	}

	mPlayer = new Player();
	auto spawnPoint = mMap->GetPlayerSpawnPoint();
	spawnPoint.y -= 100.0f;
	mPlayer->SetPosition(spawnPoint);
	mPlayer->SetState(new PlayerFallingState(mPlayer));
	mPlayer->SetShield(new Shield(mPlayer));

	
	// -----GunEnemy-----
	enemy = new GunEnemy(D3DXVECTOR3(688.0f, 323.0f, 0.f));
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	/*gunEnemy3 = new GunEnemy(D3DXVECTOR3(776.0f, 416.0f, 0.f));*/
	enemy = new GunEnemy(D3DXVECTOR3(944.0f, 323.0f, 0.f));
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	// ------------------

	// -----MissileEnemy-----
	/*enemy = new MissileEnemy(D3DXVECTOR3(344.0f, 402.0f, 0.f), 1);*/
	enemy = new MissileEnemy(D3DXVECTOR3(470.0f, 402.0f, 0.f), 2);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	enemy = new MissileEnemy(D3DXVECTOR3(380.0f, 402.0f, 0.f), 2);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	enemy = new MissileEnemy(D3DXVECTOR3(600.0f, 402.0f, 0.f), 0);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	enemy = new MissileEnemy(D3DXVECTOR3(1577, 402.0f, 0.f), 1);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	// ----------------------

	// -----RunEnemy-----
	enemy = new RunEnemy();
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	enemy = new RunEnemy(D3DXVECTOR3(376.0f, 402.0f, 0.f), 1);
	mEnemies.push_back(enemy);
	mGrid->Add(enemy);
	//----------------

	for (size_t i = 0; i < mEnemies.size(); ++i)
	{
		EnemyType type = mEnemies[i]->GetEnemyType();
		switch (type)
		{
		case EBatEnemy:
			break;
		case EFlyEnemy:
			break;
		case ERunEnemy:
			mEnemies[i]->SetBullet(new NormalBullet(mEnemies[i]));
			mGrid->Add(mEnemies[i]->GetBullet());
			break;
		case EGunEnemy:
			mEnemies[i]->SetBullet(new NormalBullet(mEnemies[i]));
			mGrid->Add(mEnemies[i]->GetBullet());
			std::cout << "Test bullet" << mEnemies[i]->GetBullet() << std::endl;
			break;
		case EGunStockEnemy:
			break;
		case EMissileEnemy:
			break;
		case EDefaultEnemy:
			break;
		case EBossCharleston:
			break;
		default:
			break;
		}
	}
	

	mCamera = new Camera(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());
	mMap->SetCamera(mCamera);

	CheckCamera(.0f);
}

void DemoScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	mGrid->GetEntities(mCamera->GetBound(), mEntities);

	bool collisionWithGround = false;
	for (Entity* entity: mEntities)
	{
		auto type = entity->GetCollidableObjectType();
		switch (type)
		{
		case EBullet:
			break;
		case EEnemy:
			((Enemy*)entity)->Update(deltaTime, mPlayer);
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::EGunEnemy)
			{
				((GunEnemy*)entity)->GetBullet()->Update(deltaTime);
			}
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::ERunEnemy)
			{
				((RunEnemy*)entity)->GetBullet()->Update(deltaTime);
			}
			break;
		default:
			entity->Update(deltaTime);
			if (type == EPlatform)
			{
				RECT pB = mPlayer->GetBoundingBox();
				RECT eB = entity->GetBoundingBox();
				GroundType type = ((Ground*)entity)->GetGroundType();

				if (abs(eB.top - pB.bottom) <= 5 && (pB.left >= eB.left && pB.left <= eB.right || pB.right >= eB.left && pB.right <= eB.right))
				{
					collisionWithGround = true;
				}
			}
			break;
		}
	}
	mPlayer->shouldFall = !collisionWithGround;

	// Check collision
	std::vector<CollisionEvent*> cEvents;
	mPlayer->CalcCollision(&mEntities, cEvents);
	mPlayer->OnCollision(cEvents);

	// Check shield collision
	cEvents.clear();
	mPlayer->GetShield()->CalcCollision(&mEntities, cEvents);
	mPlayer->GetShield()->OnCollision(cEvents);

	Keyboard* keyboard = SceneManager::GetInstance().GetKeyboard();

	mPlayer->HandleKeyboard(keyboard);
	mPlayer->Update(deltaTime);
	mPlayer->GetShield()->Update(deltaTime);
	CheckCamera(deltaTime);
	CheckChageMap();
}

void DemoScene::Draw()
{
	D3DXVECTOR2 trans = mCamera->GetTransform();

	// Draw Map
	mMap->Draw(trans);

	// Draw Entities
	for (Entity* entity: mEntities)
	{

		auto type = entity->GetCollidableObjectType();
		switch (type)
		{
		case EEnemy:
			((Enemy*)entity)->Draw(trans);
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::EGunEnemy)
			{
				((GunEnemy*)entity)->GetBullet()->Draw(trans);
			}
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::EMissileEnemy)
			{
				/*((GunEnemy*)entity)->GetBullet()->Draw(trans);*/
			}
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::ERunEnemy)
			{
				((RunEnemy*)entity)->GetBullet()->Draw(trans);
			}
			if (((Enemy*)entity)->GetEnemyType() == EnemyType::EBossCharleston)
			{
				/*((GunEnemy*)entity)->GetBullet()->Draw(trans);*/
			}
			break;
		default:
			entity->Draw(trans);
			break;
		}
	}

	// Draw player
	mPlayer->Draw(trans);
	// Draw shield
	mPlayer->GetShield()->Draw(trans);
	Scene::Draw();
}

void DemoScene::CheckCamera(float deltaTime)
{
	D3DXVECTOR3 playerPos = mPlayer->GetPosition();
	//playerPos.x += mPlayer->GetWidth() / 2.0f;
	//playerPos.y += mPlayer->GetHeight() / 2.0f;

	if (mCamera->GetPosition() == D3DXVECTOR3(.0f, .0f, .0f))
	{
		mCamera->SetPosition(playerPos);
	}
	else
	{
		float lerpX = 5.0f;
		float lerpY = 5.0f;
		D3DXVECTOR3 camPos = mCamera->GetPosition();

		float dX = 1.0f * (playerPos.x - camPos.x) * lerpX * deltaTime;
		float dY = 1.0f * (playerPos.y - camPos.y) * lerpY * deltaTime;

		mCamera->AddPositionX((int)dX);
		mCamera->AddPositionY((int)dY);
	}


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
	/*else if (MapID == ID_MAP_CHARLESTON_BOSS_LIGHT)
	{
		if (mPlayer->GetPosition().x >= DEMO_EXIT_MINIMAP)
			this->ChangeMap(ID_MAP_PITTSBURGH_DARK);
	}*/
}
