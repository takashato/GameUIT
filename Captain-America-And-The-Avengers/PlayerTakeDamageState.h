#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerTakeDamageState : public PlayerState
{
public:
	PlayerTakeDamageState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

