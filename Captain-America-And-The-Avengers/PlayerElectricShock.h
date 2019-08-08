#pragma once
#include "PlayerState.h"

class PlayerElectricShock : public PlayerState
{
public:
	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) override;
	virtual Data Exit(Player& player, EPlayerState toState) override;
	virtual void Update(Player& player, float deltaTime) override;
	virtual void HandleKeyboard(Player& player, Keyboard* keyboard) override;
	virtual void OnKeyDown(Player& player, BYTE code) override;
	virtual void OnKeyUp(Player& player, BYTE code) override;
	virtual void OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent) override;

	EPlayerState GetState() { return EPlayerState::ElectricShock; }

private:
	EPlayerState pendingSwitchState;
	float posxWhenGotInjure;
	float posyWhenGotInjure;
	float DistanceLeftToClimb;
	float maxTimeHold = 0;

	float holdingDistance = 0.0f;

	float mCounter = 0.0f;

};

