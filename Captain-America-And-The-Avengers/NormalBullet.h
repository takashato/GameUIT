#pragma once
#include "Animation.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"

#define NORMALBULLET_FLYING_STATE 0

class NormalBullet : public Bullet
{
public:
	NormalBullet(D3DXVECTOR3 position = D3DXVECTOR3(304.0f, 402.0f, 0.f));
	~NormalBullet();
	void LoadAnimations();

	void Update(float deltaTime, GunEnemy* gunEnemy);
	void Draw(D3DXVECTOR2 transform);

	int GetState();

	void OnSetPosition();

	BulletType GetBulletType();

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	Animation* mAniFlying = NULL;
	int mState = -1;
	float mCounter = 0;
	bool isDraw = true;
};

