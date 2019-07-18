#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerHighShieldingState : public PlayerState
{
public:
	PlayerHighShieldingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

