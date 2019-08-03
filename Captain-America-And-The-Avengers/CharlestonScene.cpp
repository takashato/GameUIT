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
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
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
	mPlayer->SetPosition(mData.GetSpawnPoint("Player1"));
	mPlayer->SetShield(new Shield(mPlayer.get()));

	// Update Camera for the first time
	mCamera->Update(mPlayer->GetCenterPoint());

	// Load Map Object
	// Ground
	for (DataGround dataGround : mData.GetDataGround())
	{
		mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
	}
	// Enemy
	for (DataEnemy dataEnemy : mData.GetDataEnemy())
	{
		switch (dataEnemy.type)
		{
		case EGunEnemy:
		{
			GunEnemy* enemy = new GunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f));
			enemy->SetBullet(new NormalBullet(enemy));
			mGrid->Add(enemy);
		}
			break;
		case EMissileEnemy:
			mGrid->Add(new MissileEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType));
			break;
		case ERunEnemy:
			mGrid->Add(new RunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType));
			break;
		}
	}

}

void CharlestonScene::Update(float deltaTime)
{
	mGrid->Update(deltaTime, mCamera->GetBound(), mPlayer.get());
	std::vector<CollisionEvent*> cEvent;
	mPlayer->CalcCollision(&mGrid->mTemp, cEvent);
	mPlayer->OnCollision(cEvent);
	mPlayer->HandleKeyboard(SceneManager::GetInstance().GetKeyboard());
	mPlayer->Update(deltaTime);
	cEvent.clear();
	mPlayer->GetShield()->CalcCollision(&mGrid->mTemp, cEvent);
	mPlayer->GetShield()->OnCollision(cEvent);
	mPlayer->GetShield()->Update(deltaTime);
	mCamera->Update(mPlayer->GetCenterPoint());
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

void CharlestonScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void CharlestonScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}