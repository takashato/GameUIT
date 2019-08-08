#include "pch.h"
#include "Game.h"
#include "CharlestonScene.h"

CharlestonScene::CharlestonScene() : Scene("Resources\\Map\\Charleston_Map.xml")
{
	Setup();
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CLoopSound(GetBgMusic());
	}
}

CharlestonScene::~CharlestonScene()
{
}

void CharlestonScene::Setup()
{
	// Camera
	mCamera = std::make_unique<Camera>(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

	// Load map
	mMap = std::make_unique<GameMap>(ID_MAP_CHARLESTON, CA2W(mData.GetTilemapImagePath()), CA2W(mData.GetTilemapMatrixPath()));
	mMap->SetCamera(mCamera.get());
	mCamera->SetWorldBoundary(mMap->GetBoundary());

	// Create grid
	mGrid = std::make_unique<Grid>(mMap->GetWidth(), mMap->GetHeight());

	// Create player
	mPlayer = std::make_unique<Player>();
	mPlayer->SetPosition(mData.GetSpawnPoint("Player"));
	mPlayer->SetShield(new Shield(mPlayer.get()));

	// Update Camera for the first time
	mCamera->Update(mPlayer->GetCenterPoint());

	// Load Map Object
	// Ground
	for (DataGround dataGround : mData.GetDataGround())
	{
		switch (dataGround.type)
		{
		case EGroundDynamic:
		{
			DynamicGround* ground = new DynamicGround(D3DXVECTOR3(dataGround.x, dataGround.y, .0f),dataGround.subType);
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
		{
			mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
		}
		break;
		}
	}
	// Enemy
	for (DataEnemy dataEnemy : mData.GetDataEnemy())
	{
		mGrid->Add(new Spawner(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy));
	}
	// Transport Area
	mGrid->Add(new TransportArea(D3DXVECTOR3(1979.0f, 358.0f, .0f), 16, 90));

	// Capsule
	for (DataCapsule dataCapsule : mData.GetDataCapsule())
	{
		auto capsule = new Capsule(D3DXVECTOR3(dataCapsule.x, dataCapsule.y, .0f), dataCapsule.itemList);
		mGrid->Add(capsule);
	}
}

void CharlestonScene::Update(float deltaTime)
{
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
}

void CharlestonScene::Draw()
{
	auto trans = mCamera->GetTransform();
	mMap->Draw(trans);
	mGrid->Draw(trans);
	mPlayer->Draw(trans);
	mPlayer->GetShield()->Draw(trans);
}

SoundType CharlestonScene::GetBgMusic()
{
	return SoundType::ThemeOfCaptainAmerica;
}

void CharlestonScene::Transport()
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
	SceneManager::GetInstance().ChangeScene(MapID::CharlestonBoss);
}

void CharlestonScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void CharlestonScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}

