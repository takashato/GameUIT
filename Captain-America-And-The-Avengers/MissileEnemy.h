#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define MISSILEENEMY_STANDING_STATE 0
#define MISSILEENEMY_SITTING_STATE 1
#define MISSILEENEMY_RUNNING_STATE 2
#define MISSILEENEMY_JUMPING_STATE 3
#define MISSILEENEMY_FALLING_STATE 4
#define MISSILEENEMY_TAKEDAMAGE_STATE 5
#define MISSILEENEMY_DYING_STATE 6

class MissileEnemy : public Entity
{
public:
	MissileEnemy(D3DXVECTOR3 position = D3DXVECTOR3(344.0f, 416.0f, 0.f));
	~MissileEnemy();
	void LoadAnimations();

	void Update(float deltaTime, Player* player, int id);
	void Draw(D3DXVECTOR2 transform);

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	/*void SetCamera(Camera* camera);*/
	RECT GetBoundingBox();


private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniSitting = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniJumping = NULL;
	Animation* mAniFalling = NULL;
	Animation* mAniTakeDamage = NULL;
	Animation* mAniDying = NULL;
	Animation* mCurrentAni = NULL;
	int mState = -1;

	/*Camera* mCamera;*/
	float mCounter = 0;
};

