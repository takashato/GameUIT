#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSittingOnShieldState : public PlayerState
{
public:
	PlayerSittingOnShieldState(Player* player);
	EPlayerState GetState();
	void Update(float deltaTime);

	void HandleKeyboard(Keyboard *keyboard);
};

