#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 
#include "AnimationScript.h"

class Player : public Entity
{
public:
	Player();
	void LoadAnimations();

	void Update(float deltaTime);
	void Draw();
	void HandleKeyboard(Keyboard& keyboard);

	PlayerState* GetState();
	void SetState(PlayerState* state);

	void ChangeAnimationByState(EPlayerState state);

	void OnSetPosition();

private:
	Sprite* mSprite = NULL;
	AnimationScript* mAniScripts = NULL;
	
	Animation* mAniStanding = NULL;
	Animation* mAniRunning = NULL;

	Animation* mCurrentAni = NULL;

	PlayerState* mState;
};