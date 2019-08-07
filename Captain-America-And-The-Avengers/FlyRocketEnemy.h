#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define FLYROCKETENEMY_FLY_STATE 0
#define FLYROCKETENEMY_GUN_STATE 1
#define FLYROCKETENEMY_DYING_STATE 0




class FlyRocketEnemy : public Enemy
{
public:
	FlyRocketEnemy(D3DXVECTOR3 position, int subTypeID);
	~FlyRocketEnemy();
	void LoadAnimations();

	void Update(float deltaTime, Player* player);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	EnemyType GetEnemyType();
	void CheckDirection(Player* player);


	
private:
	int mFlagMove = 1;
	bool isShootOke = true;
	D3DXVECTOR2 mCenterEllipse;
	D3DXVECTOR2 mTransformEllipse;
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniFlying = NULL;
	Animation* mAniGunning = NULL;
	Animation* mAniDying = NULL;
	int mState = -1;

	float mCounter = 0;
	int mSubTypeID = 0;
};

