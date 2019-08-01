#pragma once
#include "Animation.h"
#include "Enemy.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"
#include "NormalBullet.h"

#define GUNENEMY_STANDING_STATE 0
#define GUNENEMY_SITTING_STATE 1
#define GUNENEMY_DYING_STATE 2

class GunEnemy : public Enemy
{
public:
	GunEnemy(D3DXVECTOR3 position = D3DXVECTOR3(300.0f, 402.0f, 0.f));
	~GunEnemy();
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

	void OnDie();

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniSitting = NULL;
	Animation* mAniDying = NULL;
	int mState = -1;

	/*Camera* mCamera;*/
	float mCounter = 0;

	NormalBullet* mBullet;
};

