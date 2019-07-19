#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerInvincibleStandState : public PlayerState
{
public:
	PlayerInvincibleStandState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};

