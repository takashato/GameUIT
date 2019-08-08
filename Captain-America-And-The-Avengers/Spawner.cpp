#include "pch.h"
#include "SceneManager.h"
#include "Spawner.h"

Spawner::Spawner(D3DXVECTOR3 position, DataEnemy enemyData, float spawnInterval)
{
	this->spawnInterval = spawnInterval;
	dataEnemy = enemyData;
	mPosition = position;
	mWidth = 16;
	mHeight = 16;
}

Spawner::~Spawner()
{
}

RECT Spawner::GetBoundingBox()
{
	RECT rect;
	rect.left = mPosition.x;
	rect.top = mPosition.y;
	rect.right = rect.left + mWidth;
	rect.bottom = rect.top + mHeight;
	return rect;
}

CollidableObjectType Spawner::GetCollidableObjectType()
{
	return CollidableObjectType::ESpawner;
}

void Spawner::Update(float deltaTime)
{
	if (!mIsActivted) return;

	if (mEnemy == nullptr)
	{
		mCounter += deltaTime;
		if (mCounter >= spawnInterval || !spawnFirstTime)
		{
			Spawn();
			mCounter = .0f;
		}
	}
}

void Spawner::Draw(D3DXVECTOR2 trans)
{
	this->RenderBoundingBox(trans);
}

void Spawner::Spawn()
{
	if (!GeoUtils::IsIntersect(GetBoundingBox(), SceneManager::GetInstance().GetScene()->GetCamera()->GetBound())
		|| !spawnFirstTime || spawnInterval == .0f
		)
	{
		if (mEnemy != nullptr) return;

		auto mGrid = SceneManager::GetInstance().GetScene()->GetGrid();
		Enemy * enemy = nullptr;
		switch (dataEnemy.type)
		{
		case EGunEnemy:
		{
			enemy = new GunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType);
		}
		break;
		case EMissileEnemy:
			enemy = new MissileEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType);
			break;
		case ERunEnemy:
			enemy = new RunEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType);
			break;
		case EGunStockEnemy:
			enemy = new GunStock(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f));
			break;
		case EBatEnemy:
			enemy = new Bat(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f), dataEnemy.subType);
			break;
		case EFlyEnemy:
			enemy = new FlyRocketEnemy(D3DXVECTOR3(dataEnemy.x, dataEnemy.y, .0f));
			break;
		}

		if (enemy != nullptr) // Add to grid
		{
			if (!spawnFirstTime) spawnFirstTime = true;
			std::cout << "Spawn enemy.\n";
			enemy->spawner = this;
			mGrid->Add(enemy);
			this->mEnemy = enemy;
		}
	}
}

void Spawner::OnDelete()
{
	killCounter++;
	std::cout << "Enemy controlled by this spawner has been deleted.\n";
	this->mEnemy = nullptr;
}
