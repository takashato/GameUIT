#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h"
#include "PlayerLowPunchingState.h"
#include "Entity.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(Player* player);

	void HandleKeyboard(Keyboard *keyboard);
	void Update(float deltaTime);

	EPlayerState GetState();

protected:
	float mTimeUpdater = .0f;
	
};