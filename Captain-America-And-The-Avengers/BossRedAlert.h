#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"
#include "RedAlertBullet.h"

#define BOSSREDALERT_IDLE_STATE 0
#define BOSSREDALERT_TOSS_THE_BARREL_STATE 1
#define BOSSREDALERT_RUNNING_STATE 2
#define BOSSREDALERT_GUN_STATE 3
#define BOSSREDALERT_CRAZY_STATE 4




class BossRedAlert : public Enemy
{
public:
	BossRedAlert(D3DXVECTOR3 position);
	~BossRedAlert();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	void TakeDamage(Entity* source, int damage = 1);
	void SetInvincible(bool val);

	void CheckDirection(Player* player);

	//
	int mCountGun = 0;

private:
	int mHP = 20;
	D3DXVECTOR3 mCenter;
	bool isDown = true;
	int amplitudeA = 63, amplitudeB = 23;
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniIdle = NULL;
	Animation* mAniTossTheBarrel = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniGun = NULL;
	Animation* mAniCrazy = NULL;

	int mState = -1;

	float mCounter = 0;
	float mCounterBeHit = 0;
	bool mIsInvincible = false;
	float mInvincibleCounter = .0f;

	D3DXVECTOR3 playerPos;
};

