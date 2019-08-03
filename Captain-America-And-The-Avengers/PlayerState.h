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
	PlayerState();

	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) = 0;
	virtual Data Exit(Player& cap, EPlayerState toState) = 0;
	virtual void Update(float deltaTime) = 0;

	virtual EPlayerState GetState();
	virtual void HandleKeyboard(Keyboard* keyboard) = 0;

	virtual void OnKeyDown(BYTE code) = 0;
	virtual void OnKeyUp(BYTE code) = 0;

	virtual void OnCollision(CollisionEvent* ce) = 0;
protected:
	Player* mPlayer = nullptr;
};