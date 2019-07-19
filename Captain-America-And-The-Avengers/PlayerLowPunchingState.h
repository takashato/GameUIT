#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerLowPunchingState : public PlayerState
{
public:
	PlayerLowPunchingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

