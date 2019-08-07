#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "AnimationScript.h"

class GunEnemy;
class RunEnemy;
class Bullet;

class BossVipBullet : public Bullet
{
public:
	BossVipBullet(D3DXVECTOR3 position, int flyDirection, int flyDirectionY = 0);
	~BossVipBullet();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();

	void OnSetPosition();

	BulletType GetBulletType();

	void HitShield();

private:
	static Sprite* mSprite;
	static AnimationScript* mAniScripts;
	static Animation* mAniFly, * mAniFlyLeftDown, * mAniFlyDown;

	float mCounter = 0;
	bool isFired = true;

	int mFlyDirection = 0;
	int mFlyDirectionY = 0;

	static constexpr auto BULLET_SPEED = 250.0f;
	static constexpr auto DELTA_CAM_TO_DESTROY = .0f;
};

