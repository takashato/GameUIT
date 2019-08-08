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
	for (DataEnemy dataEnemy : mData.GetDataEnemy())
	{
		mGrid->Add(new Spawner(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy));
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
	// Capsule
	for (DataCapsule dataCapsule : mData.GetDataCapsule())
	{
		auto capsule = new Capsule(D3DXVECTOR3(dataCapsule.x, dataCapsule.y, .0f), dataCapsule.itemList);
		mGrid->Add(capsule);
	}
	// Button
	mGrid->Add(new LightButton(D3DXVECTOR3(270.0f, 48.0f, .0f)));
	//IronBar
	for (DataIronBar dataIronBar : mData.GetDataIronBar())
	{
		mGrid->Add(new IronBar(D3DXVECTOR3(dataIronBar.x, dataIronBar.y, .0f), dataIronBar.w, dataIronBar.h));
	}
}

void PittsburghScene::Update(float deltaTime)
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

void PittsburghScene::Draw()
{
	auto trans = mCamera->GetTransform();
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
void PittsburghScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void PittsburghScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}
