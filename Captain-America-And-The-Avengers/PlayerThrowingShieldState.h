#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerThrowingShieldState : public PlayerState
{
public:
	PlayerThrowingShieldState(Player* player);
	EPlayerState GetState();
	void Update(float deltaTime);
	void HandleKeyboard(Keyboard *keyboard);
protected:
	bool isHaveShield = true;
	float mTimeUpdater = .0f;
};

