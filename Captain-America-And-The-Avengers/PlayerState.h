#pragma once
#include "Keyboard.h"

class Entity;
class Player;
struct CollisionEvent;

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
	SittingOnShield,
	Swimming,
	Cling
};

class PlayerState
{
public:
	PlayerState(Player* player);
	Player* GetPlayer();

	virtual void Update(float deltaTime);

	virtual EPlayerState GetState();
	virtual void HandleKeyboard(Keyboard* keyboard);

	virtual void OnCollision(CollisionEvent* ce);

protected:
	Player* mPlayer = nullptr;
};