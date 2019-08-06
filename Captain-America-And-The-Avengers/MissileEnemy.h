#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define MISSILEENEMY_STANDING_STATE 0
#define MISSILEENEMY_SITTING_STATE 1
#define MISSILEENEMY_RUNNING_STATE 2
#define MISSILEENEMY_JUMPING_STATE 3
#define MISSILEENEMY_FALLING_STATE 4
#define MISSILEENEMY_DYING_STATE 5

class MissileEnemy : public Enemy
{
	static constexpr auto RUN_SPEED = 25.0f;

public:
	MissileEnemy(D3DXVECTOR3 position = D3DXVECTOR3(344.0f, 416.0f, 0.f), int subTypeID = 1);
	~MissileEnemy();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	EnemyType GetEnemyType();
	Bullet* GetBullet();
	void SetBullet(Bullet* Bullet);

	void OnAttacked();
	void OnDie();
	void TakeDamage(Entity* source, int hp);
	void SetInvincible(bool val);

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniSitting = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniJumping = NULL;
	Animation* mAniFalling = NULL;
	Animation* mAniDying = NULL;
	int mState = -1;
	D3DXVECTOR3 spawnPosition;
	/*Camera* mCamera;*/
	float mCounter = 0;
	NormalBullet* mBullet;
	int mSubTypeID = 0;
	bool isMeetPlayer = false;
	bool isJump = false;
	int changeDirection = 1;
};

