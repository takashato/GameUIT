#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);

	void Update(float deltaTime);
private:
	float mCounter = .0f;

};

