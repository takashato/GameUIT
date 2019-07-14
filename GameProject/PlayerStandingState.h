#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard& keyboard);
};