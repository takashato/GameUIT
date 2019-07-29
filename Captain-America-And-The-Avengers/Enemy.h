#pragma once
#include "Entity.h"
#include "Player.h"

enum EnemyType
{
	EBatEnemy,
	EFlyEnemy,
	ERunEnemy,
	EGunEnemy,
	EGunStockEnemy,
	EMissileEnemy,
	EDefaultEnemy
};

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	virtual void Update(float deltaTime, Player* player) = 0;
	virtual void Draw(D3DXVECTOR2 transform) = 0;

	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;
	virtual EnemyType GetEnemyType();

protected:
	Animation* mCurrentAni = NULL;
};