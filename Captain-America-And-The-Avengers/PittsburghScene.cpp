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
		switch (dataEnemy.type)
		{
		case EGunEnemy:
		{
			GunEnemy* enemy = new GunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType);
			mGrid->Add(enemy);
		}
		break;
		case EMissileEnemy:
			mGrid->Add(new MissileEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType));
			break;
		case ERunEnemy:
			mGrid->Add(new RunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType));
			break;
		case EGunStockEnemy:
			mGrid->Add(new GunStock(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f)));
			break;
		case EBatEnemy:
			mGrid->Add(new Bat(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType));
			break;
		case EFlyEnemy:
			mGrid->Add(new FlyRocketEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f)));
			break;
		}
	}
	// Ground
	for (DataGround dataGround : mData.GetDataGround())
	{
		mGrid->Add(new Ground(D3DXVECTOR3(dataGround.x, dataGround.y, .0f), dataGround.type, dataGround.w, dataGround.h));
	}
	// Capsule
	for (DataCapsule dataCapsule : mData.GetDataCapsule())
	{
		auto capsule = new Capsule(D3DXVECTOR3(dataCapsule.x, dataCapsule.y, .0f), dataCapsule.itemList);
		mGrid->Add(capsule);
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
void PittsburghScene::Transport(TypeExtra type)
{
	if (HasBgMusic())
	{
		SoundManager::GetInstance().CStopsound(GetBgMusic());
	}
	if(type==Type1)
	{
		SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra1);
	}
	else
	{
		SceneManager::GetInstance().ChangeScene(MapID::PittsburghExtra2);
	}
	//Notes: Chua luu lai vi tri player o map chinh
}
void PittsburghScene::OnKeyUp(BYTE key)
{
	mPlayer->OnKeyUp(key);
}

void PittsburghScene::OnKeyDown(BYTE key)
{
	mPlayer->OnKeyDown(key);
}
