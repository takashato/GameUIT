#include "pch.h"
#include "Game.h"
#include "PittsburghExtra2Scene.h"


PittsburghExtra2Scene::PittsburghExtra2Scene() : Scene("Resources\\Map\\Pittsburgh_ExtraMap2.xml")
{
	Setup();
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CLoopSound(GetBgMusic());
	}
}

PittsburghExtra2Scene::~PittsburghExtra2Scene()
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
}

void PittsburghExtra2Scene::Setup()
{
	// Camera
	mCamera = std::make_unique<Camera>(Game::GetInstance().GetWidth(), Game::GetInstance().GetHeight());

	// Load map
	mMap = std::make_unique<GameMap>(ID_MAP_CHARLESTON_BOSS_LIGHT, CA2W(mData.GetTilemapImagePath()), CA2W(mData.GetTilemapMatrixPath()));
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
		mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
	}

}

void PittsburghExtra2Scene::Update(float deltaTime)
{
	mGrid->Update(deltaTime, mCamera->GetBound(), mPlayer.get());
	std::vector<CollisionEvent*> cEvent;
	mPlayer->HandleKeyboard(SceneManager::GetInstance().GetKeyboard());
	mPlayer->CalcCollision(&mGrid->mTemp, cEvent);
	mPlayer->OnCollision(cEvent);
	mPlayer->Update(deltaTime);
	mGrid->GetEntities(mCamera->GetBound(), mGrid->mTemp); // Avoid get deleted entity
	cEvent.clear();
	mPlayer->GetShield()->CalcCollision(&mGrid->mTemp, cEvent);
	mPlayer->GetShield()->OnCollision(cEvent);
	mPlayer->GetShield()->Update(deltaTime);
	mCamera->Update(mPlayer->GetCenterPoint());
}

void PittsburghExtra2Scene::Draw()
{
	auto trans = mCamera->GetTransform();
	mMap->Draw(trans);
	mGrid->Draw(trans);
	mPlayer->Draw(trans);
	mPlayer->GetShield()->Draw(trans);
}

SoundType PittsburghExtra2Scene::GetBgMusic()
{
	return SoundType::ThemeOfCaptainAmerica;
}
void PittsburghExtra2Scene::Transport()
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
	SceneManager::GetInstance().ChangeScene(MapID::Pittsburgh);
}
void PittsburghExtra2Scene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void PittsburghExtra2Scene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}

