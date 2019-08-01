#pragma once
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerKickingState.h"
#include "PlayerSittingOnShieldState.h"
#include "PlayerState.h"

class PlayerHighJumpState : public PlayerState
{
public:
	PlayerHighJumpState(Player* player);
	~PlayerHighJumpState();

	void HandleKeyboard(Keyboard* keyboard);
	void Update(float deltaTime);

	EPlayerState GetState();
private:
	float mTimeCounter = .0f, mTimeUpdater = .0f;
	int mRunState = 0;
};

