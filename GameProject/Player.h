#pragma once

#include "Animation.h"
#include "Entity.h"

enum PlayerState 
{
	Normal,
	Running
};

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void Draw();

	PlayerState GetState();
	void SetState(PlayerState state);

	void OnSetPosition();

private:
	Animation* mAniNormal = NULL;
	Animation* mAniRunning = NULL;
	Animation* mCurrentAni = NULL;

	PlayerState mState = Normal;
};