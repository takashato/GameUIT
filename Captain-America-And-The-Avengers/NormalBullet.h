#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"

#define NORMALBULLET_FLYING_STATE 0

class GunEnemy;
class RunEnemy;
class Bullet;

class NormalBullet : public Bullet
{
public:
	NormalBullet(D3DXVECTOR3 position, int flyDirection);
	~NormalBullet();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw(D3DXVECTOR2 transform);

	int GetState();

	void OnSetPosition();

	BulletType GetBulletType();

	void HitShield();

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	Animation* mAniFlying = NULL;

	float mCounter = 0;
	bool isFired = true;

	int mFlyDirection = 0;

	static constexpr auto BULLET_SPEED = 150.0f;
	static constexpr auto DELTA_CAM_TO_DESTROY = 10.0f;
};

