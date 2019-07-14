#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "Entity.h"

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(Player* player);

	void HandleKeyboard(Keyboard& keyboard);

	EPlayerState GetState();

protected:
	float mAcceleratorX;
};