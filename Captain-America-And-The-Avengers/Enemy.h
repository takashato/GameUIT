#pragma once
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Grid.h"

class Bullet;
class Spawner;

class Enemy : public Entity
{
	friend class Spawner;

public:
	Enemy();
	~Enemy();

	virtual void Update(float deltaTime, Player* player);
	virtual void Draw(D3DXVECTOR2 transform) = 0;

	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;
	virtual EnemyType GetEnemyType();

	virtual void TakeDamage(Entity* source, int hp = 1);
	virtual void SetInvincible(bool val);

	virtual void OnAttacked();
	virtual void OnDie();

	Spawner* GetSpawner() { return spawner; };
	
	void OnSetPosition();

	bool pendingDelete = false;

protected:
	int mHP = 1;
	bool mIsInvincible = false;
	float mInvincibleCounter = .0f;

	Animation* mCurrentAni = NULL;

	Spawner* spawner = nullptr;

};