#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "AnimationScript.h"

class GunEnemy;
class RunEnemy;
class Bullet;

class Barrel : public Bullet
{
public:
	Barrel(D3DXVECTOR3 position, int flyDirection, float playerX, int flyDirectionY = 0);
	~Barrel();
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
	static Animation* mAniBarrel;

	float mCounter = 0;
	bool isFired = true;

	int mFlyDirection = 0;
	int mFlyDirectionY = 0;

	static constexpr auto BULLET_SPEED = 10.0f;
	static constexpr auto DELTA_CAM_TO_DESTROY = 10.0f;
	float mA;
};


