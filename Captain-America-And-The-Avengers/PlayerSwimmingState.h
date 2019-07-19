#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSwimmingState : public PlayerState
{
public:
	PlayerSwimmingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

