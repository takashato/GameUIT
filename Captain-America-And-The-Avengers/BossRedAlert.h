#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"
#include "RedAlertBullet.h"
#include "Dynamite.h"

#define BOSSREDALERT_IDLE_STATE 0
#define BOSSREDALERT_TOSS_THE_BARREL_STATE 1
#define BOSSREDALERT_RUNNING_STATE 2
#define BOSSREDALERT_GUN_STATE 3
#define BOSSREDALERT_CRAZY_STATE 4
#define BOSSREDALERT_HURT_STATE 5
#define BOSSREDALERT_CHANGE_STATUS_STATE 6
#define BOSSREDALERT_DYING_STATE 7




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

	void TakeDamageBossRedAlertNotCrazy(Entity* source, int damage = 8);
	void SetInvincible(bool val);

	void CheckDirection(Player* player);

	//
	void TakeDamage(Entity* source, int damage = 2);

	int mCountGun = 0;

	RECT GetBoundingBox();

private:
	int mHP = 20;

	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniIdle = NULL;
	Animation* mAniTossTheBarrel = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniGun = NULL;
	Animation* mAniCrazy = NULL;
	Animation* mAniHurt = NULL;
	Animation* mAniDying = NULL;

	int mState = -1;

	float mCounter = 0;
	float mCounterBeHit = 0;
	bool mIsInvincible = false;
	float mInvincibleCounter = .0f;
	float mCounterDie = 0;

	bool thrownDynamite = false;

	Dynamite* dynamite = nullptr;

	D3DXVECTOR3 playerPos;
};

