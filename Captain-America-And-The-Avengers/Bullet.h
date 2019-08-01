#pragma once
#include "Entity.h"
#include "Enemy.h"

enum BulletType
{
	BNormalBullet,
	BBigMissile,
	BLittleMissile,
	BBossNormalBullet,
	BBossVipBullet,
	BDefaultBullet
};

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(D3DXVECTOR2 transform) = 0;

	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;
	virtual BulletType GetBulletType();

	void OnSetPosition();

	void HitShield();

protected:
	Animation* mCurrentAni = NULL;

	int mFlyDirection = 0;

	bool mIsHitShield = false;
};

