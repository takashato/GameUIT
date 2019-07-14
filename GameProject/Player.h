#pragma once
#include "Animation.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerStandingState.h" 

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void Draw();
	void HandleKeyboard(Keyboard& keyboard);

	PlayerState* GetState();
	void SetState(PlayerState* state);

	void ChangeAnimationByState(EPlayerState state);

	void OnSetPosition();

private:
	Animation* mAniStanding = NULL;
	Animation* mAniRunning = NULL;

	Animation* mCurrentAni = NULL;

	PlayerState* mState;
};