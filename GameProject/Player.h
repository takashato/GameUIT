#pragma once

#include "Animation.h"
#include "Entity.h"

#define PLAYER_STATE_NORMAL 1
#define PLAYER_STATE_RUNNING 2

typedef char PLAYER_STATE;

class Player : public Entity
{
public:
	Player();

	void Update(float deltaTime);
	void Draw();

	PLAYER_STATE GetState();
	void SetState(PLAYER_STATE state);

	void OnSetPosition();

private:
	Animation* mAniNormal = NULL;
	Animation* mAniRunning = NULL;
	Animation* mCurrentAni = NULL;

	PLAYER_STATE mState = PLAYER_STATE_NORMAL;
};