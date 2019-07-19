#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSittingOnShieldState : public PlayerState
{
public:
	PlayerSittingOnShieldState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

