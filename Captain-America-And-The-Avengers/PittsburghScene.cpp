#include "pch.h"
#include "Game.h"
#include "PittsburghScene.h"


PittsburghScene::PittsburghScene() : Scene("Resources\\Map\\Pittsburgh_Map.xml")
{
	Setup();
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CLoopSound(GetBgMusic());
	}
}

PittsburghScene::~PittsburghScene()
{
	
}

void PittsburghScene::Setup()
{
	// Camera
	mCamera = std::make_unique<Camera>(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

	// Load map
	mMap = std::make_unique<GameMap>(ID_MAP_PITTSBURGH_DARK, CA2W(mData.GetTilemapImagePath()), CA2W(mData.GetTilemapMatrixPath()));
	mMap->SetCamera(mCamera.get());
	mCamera->SetWorldBoundary(mMap->GetBoundary());
	//Map Dark
	mMapLight = std::make_unique<GameMap>(ID_MAP_PITTSBURGH_LIGHT, L"Resources\\Map\\Pittsburgh_Light_Map.png", L"Resources\\Map\\Matrix_Pittsburgh_Light_Map.txt");
	mMapLight->SetCamera(mCamera.get());
	// Create grid
	mGrid = std::make_unique<Grid>(mMap->GetWidth(), mMap->GetHeight());

	// Create player
	mPlayer = std::make_unique<Player>();
	mPlayer->SetPosition(mData.GetSpawnPoint("Player"));
	mPlayer->SetShield(new Shield(mPlayer.get()));

	// Update Camera for the first time
	mCamera->Update(mPlayer->GetCenterPoint());

	// Load Map Object
	// Capsule
	for (DataCapsule dataCapsule : mData.GetDataCapsule())
	{
		auto capsule = new Capsule(D3DXVECTOR3(dataCapsule.x, dataCapsule.y, .0f), dataCapsule.itemList);
		mGrid->Add(capsule);
	}
	// Ground
	for (DataGround dataGround : mData.GetDataGround())
	{
		switch (dataGround.type)
		{
		case EGroundDynamic:
		{
			DynamicGround* ground = new DynamicGround(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.subType);
			mGrid->Add(ground);
		}
		break;
		case EGroundBreak:
		{
			BreakGround* breakGr = new BreakGround((D3DXVECTOR3(dataGround.x, dataGround.y, .0f)));
			mGrid->Add(breakGr);
		}
		break;
		case EGroundHard:
		case EGroundNormal:
		case EGroundWater:
		case EGroundThorns:
		{
			mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
		}
		break;
		}
	}



	// Button
	mGrid->Add(new LightButton(D3DXVECTOR3(270.0f, 48.0f, .0f)));
	// Door
	mGrid->Add(new Door(D3DXVECTOR3(564.0f, 148.0f, .0f), "extra1"));
	mGrid->Add(new Door(D3DXVECTOR3(820.0f, 633.0f, .0f), "extra2"));
	//IronBar
	for (DataIronBar dataIronBar : mData.GetDataIronBar())
	{
		mGrid->Add(new IronBar(D3DXVECTOR3(dataIronBar.x, dataIronBar.y, .0f), dataIronBar.w, dataIronBar.h));
	}
	//Enemy
	for (DataEnemy dataEnemy : mData.GetDataEnemy())
	{
		auto spawner = new Spawner(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy);
		mGrid->Add(spawner);
		spawnerList.emplace(spawner);
	}
	// Enemy in ambush
	auto ambushEnemy1 = new Spawner(D3DXVECTOR3(264.0f, 873.f, .0f), DataEnemy(EnemyType::ERunEnemy, 264.0f, 873.0f, 1), .0f);
	auto ambushEnemy2 = new Spawner(D3DXVECTOR3(472.0f, 870.f, .0f), DataEnemy(EnemyType::EMissileEnemy, 472.0f, 870.0f, 4), .0f);
	ambushEnemy1->SetActivate(false);
	ambushEnemy2->SetActivate(false);
	mGrid->Add(ambushEnemy1);
	mGrid->Add(ambushEnemy2);
	ambushSpawner.emplace(ambushEnemy1);
	ambushSpawner.emplace(ambushEnemy2);
	
	// Transport
	mGrid->Add(new TransportArea(D3DXVECTOR3(981.0f, 736.0f, .0f), 12, 192));
}

void PittsburghScene::Update(float deltaTime)
{
	lightInterval += deltaTime;

	mGrid->Update(deltaTime, mCamera->GetBound(), mPlayer.get());
	mGrid->GetEntities(mCamera->GetBound(), mGrid->mTemp); // Avoid get deleted entity
	std::vector<CollisionEvent*> cEvent;
	mPlayer->HandleKeyboard(SceneManager::GetInstance().GetKeyboard());
	mPlayer->CalcCollision(&mGrid->mTemp, cEvent);
	if (!mPlayer->CheckAABB(mGrid->mTemp)) return;
	if (!mPlayer->OnCollision(cEvent)) return;
	mPlayer->Update(deltaTime);
	mGrid->GetEntities(mCamera->GetBound(), mGrid->mTemp); // Avoid get deleted entity
	cEvent.clear();
	mPlayer->GetShield()->CalcCollision(&mGrid->mTemp, cEvent);
	mPlayer->GetShield()->OnCollision(cEvent);
	//mPlayer->GetShield()->CheckAABB(mGrid->mTemp);
	mPlayer->GetShield()->Update(deltaTime);
	mCamera->Update(mPlayer->GetCenterPoint());
	mGrid->GetEntities(mCamera->GetBound(), mGrid->mTemp); // Avoid get deleted entity
	CheckAmbush();
}

void PittsburghScene::Draw()
{
	auto trans = mCamera->GetTransform();
	if (isLightOn)
		mMapLight->Draw(trans);
	else
		mMap->Draw(trans);
	mGrid->Draw(trans);
	mPlayer->Draw(trans);
	mPlayer->GetShield()->Draw(trans);
}

SoundType PittsburghScene::GetBgMusic()
{
	return SoundType::ThemeOfCaptainAmerica;
}
void PittsburghScene::Transport(/*TypeExtra type*/)
{
	//if (HasBgMusic())
	//{
	//	SoundManager::GetInstance().CStopsound(GetBgMusic());
	//}
	//if(type==Type1)
	//{
	//	SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra1);
	//}
	//else
	//{
	//	SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra2);
	//}
	//Notes: Chua luu lai vi tri player o map chinh

	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
	SceneManager::GetInstance().ChangeScene(MapID::RedAlertBoss);
}
void PittsburghScene::CheckAmbush()
{
	if (passedAmbush) return;

	if (!enteredAmbush)
	{
		if (mPlayer->GetPosition().x > 401.0f && mPlayer->GetPosition().y > 768.0f
			&& mPlayer->GetPosition().x < 410.0f && mPlayer->GetPosition().y < 960.0f)
		{
			EnterAmbush();
		}
	}
	else // If are in ambushh
	{
		int total = 0;
		for (auto spawner : ambushSpawner)
		{
			total += spawner->GetKillCounter();
		}
		if (total >= 6)
		{
			LeaveAmbush();
		}
	}
}

void PittsburghScene::EnterAmbush()
{
	enteredAmbush = true;
	SoundManager::GetInstance().CStopsound(GetBgMusic());
	SoundManager::GetInstance().CPlaySound(SoundType::Ambush);
	mCamera->SetLock(true);
	for (auto spawner : spawnerList) // Process non-ambush mode enemies
	{
		spawner->SetActivate(false);
		if (spawner->GetEnemy() != nullptr)
		{
			spawner->GetEnemy()->TakeDamage(mPlayer.get(), 1000);
		}
	}
	for (auto spawner : ambushSpawner)
	{
		spawner->SetActivate(true);
	}
}

void PittsburghScene::LeaveAmbush()
{
	passedAmbush = true;
	SoundManager::GetInstance().CPlaySound(GetBgMusic());
	SoundManager::GetInstance().CStopsound(SoundType::Ambush);
	mCamera->SetLock(false);
	for (auto spawner : spawnerList) // Process non-ambush mode enemies
	{
		spawner->SetActivate(true);
	}
	for (auto spawner : ambushSpawner)
	{
		spawner->SetActivate(false);
		if (spawner->GetEnemy() != nullptr)
		{
			spawner->GetEnemy()->TakeDamage(mPlayer.get(), 1000);
		}
	}
}
void PittsburghScene::ToggleLight()
{
	if (lightInterval >= .5f)
	{
		lightInterval = .0f;
		isLightOn = !isLightOn;
	}
}


void PittsburghScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void PittsburghScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}
