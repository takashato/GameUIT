#include "pch.h"
#include "Game.h"
#include "CharlestonBossScene.h"


CharlestonBossScene::CharlestonBossScene() : Scene("Resources\\Map\\Charleston_MapBoss.xml")
{
	Setup();
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CLoopSound(GetBgMusic());
	}
}

CharlestonBossScene::~CharlestonBossScene()
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
}

void CharlestonBossScene::Setup()
{
	// Camera
	mCamera = std::make_unique<Camera>(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

	// Load map
	mMap = std::make_unique<GameMap>(ID_MAP_CHARLESTON_BOSS_LIGHT, CA2W(mData.GetTilemapImagePath()), CA2W(mData.GetTilemapMatrixPath()));
	mMap->SetCamera(mCamera.get());
	mCamera->SetWorldBoundary(mMap->GetBoundary());

	mMapDark = std::make_unique<GameMap>(ID_MAP_CHARLESTON_BOSS_DARK, L"Resources\\Map\\Chaleston_MapBoss_Dark.png", L"Resources\\Map\\Matrix_Chaleston_MapBoss_Dark.txt");
	mMapDark->SetCamera(mCamera.get());

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
		mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
	}
	// Boss
	mGrid->Add(new BossCharleston(D3DXVECTOR3(189.0f, 145.0f, .0f)));

	// Button
	mGrid->Add(new LightButton(D3DXVECTOR3(16.0f, 128.0f, .0f)));
	mGrid->Add(new LightButton(D3DXVECTOR3(80.0f, 64.0f, .0f)));
	mGrid->Add(new LightButton(D3DXVECTOR3(176.0f, 96.0f, .0f)));
}

void CharlestonBossScene::Update(float deltaTime)
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
	mPlayer->GetShield()->CheckAABB(mGrid->mTemp);
	mPlayer->GetShield()->Update(deltaTime);
	mCamera->Update(mPlayer->GetCenterPoint());
	mGrid->GetEntities(mCamera->GetBound(), mGrid->mTemp); // Avoid get deleted entity
}

void CharlestonBossScene::Draw()
{
	auto trans = mCamera->GetTransform();
	if (isLightOn)
		mMap->Draw(trans);
	else
		mMapDark->Draw(trans);
	mGrid->Draw(trans);
	mPlayer->Draw(trans);
	mPlayer->GetShield()->Draw(trans);
}

SoundType CharlestonBossScene::GetBgMusic()
{
	return SoundType::BossBattle;
}

void CharlestonBossScene::ToggleLight()
{
	if (lightInterval >= .5f)
	{
		lightInterval = .0f;
		isLightOn = !isLightOn;
	}
}

void CharlestonBossScene::Transport()
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
	SceneManager::GetInstance().ChangeScene(MapID::Pittsburgh);
}

void CharlestonBossScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void CharlestonBossScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}
