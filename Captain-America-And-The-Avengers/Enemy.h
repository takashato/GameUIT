#pragma once
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"

enum EnemyType
{
	EBatEnemy,
	EFlyEnemy,
	ERunEnemy,
	EGunEnemy,
	EGunStockEnemy,
	EMissileEnemy,
	EDefaultEnemy,
	EBossCharleston
};

class Bullet;

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
	virtual Bullet* GetBullet();
	virtual void SetBullet(Bullet* Bullet) = 0;

protected:
	Animation* mCurrentAni = NULL;
	Bullet* mBullet;
};