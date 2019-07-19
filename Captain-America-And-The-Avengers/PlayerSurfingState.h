#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSurfingState : public PlayerState
{
public:
	PlayerSurfingState(Player* player);
	EPlayerState GetState();
	void Update(float deltaTime);
	void HandleKeyboard(Keyboard *keyboard);
protected:
	float mTimeUpdater = .0f;
};

