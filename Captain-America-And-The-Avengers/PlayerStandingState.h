#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerRunningState.h"
#include "PlayerHighShieldingState.h"
#include "PlayerPunchingState.h"
#include "PlayerThrowingShieldState.h"
#include "PlayerSurfingState.h"
#include "CollisionEvent.h"
#include "Shield.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(Player* player);
	EPlayerState GetState();

	void HandleKeyboard(Keyboard *keyboard);
};