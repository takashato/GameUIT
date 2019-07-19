#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSurfingState : public PlayerState
{
public:
	PlayerSurfingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

