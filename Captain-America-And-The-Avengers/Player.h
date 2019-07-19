#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"
#include "Camera.h"

class Player : public Entity
{
public:
	Player();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw();
	void HandleKeyboard(Keyboard* keyboard);

	PlayerState* GetState();
	void SetState(PlayerState* state);

	void ChangeAnimationByState(EPlayerState state);

	void OnSetPosition();

	void SetCamera(Camera* camera);

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	
	Animation* mAniStanding = NULL;
	Animation* mAniPunching = NULL;
	Animation* mAniThrowingShield = NULL;
	Animation* mAniHighShielding = NULL;
	Animation* mAniRunning = NULL;
	Animation* mAniLowJumping = NULL;
	Animation* mAniHighJumping = NULL;
	Animation* mAniSitting = NULL;

	Animation* mCurrentAni = NULL;

	PlayerState* mState;

	Camera* mCamera;

	float mCounter;
};