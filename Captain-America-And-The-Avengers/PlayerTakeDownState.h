#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerTakeDownState : public PlayerState
{
public:
	PlayerTakeDownState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

