#pragma once
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerKickingState.h"
#include "PlayerHighJumpState.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState(Player* player);

	void HandleKeyboard(Keyboard* keyboard);
	void Update(float deltaTime);

	EPlayerState GetState();

private:
	float mTimeCounter = .0f, mTimeUpdater = .0f;
	int mRunState = 0;
	bool mKeyRelease = false;
};