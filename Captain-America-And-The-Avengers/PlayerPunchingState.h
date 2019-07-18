#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerPunchingState : public PlayerState
{
public:
	PlayerPunchingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
//	void Update(float deltaTime);
//
//protected:
//	float mTimeUpdater = .0f;
};

