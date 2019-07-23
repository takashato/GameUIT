#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define GUNENEMY_STANDING_STATE 0
#define GUNENEMY_SITTING_STATE 1
#define GUNENEMY_DYING_STATE 2
class GunEnemy : public Entity
{
public:
	GunEnemy();
	~GunEnemy();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw();

	int GetState();
	void SetState(int state);

	void ChangeAnimationByState(int state);

	void OnSetPosition();

	void SetCamera(Camera* camera);

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;

	Animation* mAniStanding = NULL;
	Animation* mAniSitting = NULL;
	Animation* mAniDying = NULL;
	Animation* mCurrentAni = NULL;
	int mState;

	Camera* mCamera;

	float mCounter;
};

