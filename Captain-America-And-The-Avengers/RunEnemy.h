#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

#define RUNENEMY_STANDING_STATE 0
#define RUNENEMY_RUNNING_STATE 1
#define RUNENEMY_DYING_STATE 2

class RunEnemy : public Entity
{
public:
	RunEnemy(D3DXVECTOR3 position = D3DXVECTOR3(776.0f, 416.0f, 0.f));
	~RunEnemy();
	void LoadAnimations();

	void Update(float deltaTime, Player* player, EntityDirection direction);
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
	Animation* mAniRunning = NULL;
	Animation* mAniDying = NULL;
	Animation* mCurrentAni = NULL;
	int mState = -1;

	/*Camera* mCamera;*/
	float mCounter = 0;
};

