#pragma once
#include "Keyboard.h"

class Player;

enum EPlayerState {
	Standing,
	Running,
	Jumping,
	HighJumping,
	Falling,
	Sitting,
	HighShielding,
	Punching,
	ThrowingShield,
	LowPunching,
	Kicking,
	TakeDamage,
	TakeDown,
	InvincibleStand,
	Surfing,
	SittingOnShield
};

class PlayerState
{
public:
	PlayerState(Player* player);
	Player* GetPlayer();

	virtual void Update(float deltaTime);

	virtual EPlayerState GetState();
	virtual void HandleKeyboard(Keyboard* keyboard);

protected:
	Player* mPlayer = nullptr;
};