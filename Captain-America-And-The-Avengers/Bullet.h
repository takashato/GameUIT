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
	friend class Grid;

public:
	Bullet();
	virtual ~Bullet() = 0;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(D3DXVECTOR2 transform) = 0;

	virtual RECT GetBoundingBox();
	virtual CollidableObjectType GetCollidableObjectType() override;
	virtual BulletType GetBulletType();

	void OnSetPosition();

	void HitShield();

	void SetState(int state);

protected:
	static Sprite* mSprite;

	int mState = -1;

	Animation* mCurrentAni = NULL;

	bool mIsHitShield = false;
};

