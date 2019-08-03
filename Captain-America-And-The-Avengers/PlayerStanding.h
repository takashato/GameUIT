#pragma once
#include "PlayerState.h"

class PlayerStanding : public PlayerState
{
public:
	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) override;
	virtual Data Exit(Player& cap, EPlayerState toState) override;
	virtual void Update(float deltaTime) override;
	virtual void HandleKeyboard(Keyboard* keyboard) override;
	virtual void OnKeyDown(BYTE code) override;
	virtual void OnKeyUp(BYTE code) override;
	virtual void OnCollision(CollisionEvent* ce) override;
	EPlayerState GetState();
};