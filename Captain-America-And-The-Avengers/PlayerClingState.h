#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerClingState : public PlayerState
{
public:
	PlayerClingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

