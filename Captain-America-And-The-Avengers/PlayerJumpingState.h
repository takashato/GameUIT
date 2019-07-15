#pragma once
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState(Player* player);

	void HandleKeyboard(Keyboard& keyboard);

	EPlayerState GetState();
};