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

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniDying = NULL;
	int mState = -1;

	/*Camera* mCamera;*/
	float mCounter = 0;
};

