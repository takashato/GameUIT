#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"
//Tam thoi
#define BOSS_CHARLESTON_IDLE_STATE 0
#define BOSS_CHARLESTON_LAUGH_STATE 1
#define BOSS_CHARLESTON_DYING_STATE 2
#define BOSS_CHARLESTON_RUNNING_STATE 3
#define BOSS_CHARLESTON_BEHIT_STATE 4
#define BOSS_CHARLESTON_GUN_STATE 5
#define BOSS_CHARLESTON_KAMEHAMEHA_STATE 6
#define BOSS_CHARLESTON_HIT_STATE 7
#define BOSS_CHARLESTON_PLY_STATE 8
#define BOSS_CHARLESTON_PLYGUN_STATE 9
#define BOSS_CHARLESTON_JUMP_STATE 10



class BossCharleston : public Enemy
{
public:
	BossCharleston(D3DXVECTOR3 position);
	~BossCharleston();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	EnemyType GetEnemyType();

	void SetBullet(Bullet* Bullet);
	Bullet* GetBullet();

	void CheckDirection(Player* player);


	void ModeOne(float deltaTime, Player* player);//Run and Hit
	void ModeTwo(float deltaTime, Player* player);//Fly and Shot when fly
	void ModeThree(float deltaTime, Player* player);//Jump
	int mNumChangeMode = 1;
	int mCountMisc = 0;

	int coutGun = 1;
	//Logic for fly
	bool mFlyUp = true;
	bool mFlyDown = false;
	bool mFlyHorizontal = false;
	//Logic for Jump
	bool mIsJump = false;
	bool mIsFalling = false;

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniDying = NULL;
	Animation* mAniLaugh = NULL;
	Animation* mAniBeHit = NULL;
	Animation* mAniGun = NULL;
	Animation* mAniKamehameha = NULL;
	Animation* mAniHit = NULL;
	Animation* mAniFly = NULL;
	Animation* mAniFlyGun = NULL;
	int mState = -1;

	float mCounter = 0;
};

