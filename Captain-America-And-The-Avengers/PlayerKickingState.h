#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerKickingState : public PlayerState
{
public:
	PlayerKickingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);

	void OnCollision(CollisionEvent* ce);
};

