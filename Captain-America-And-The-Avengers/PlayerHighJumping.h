#pragma once
#include "PlayerState.h"

class PlayerHighJumping : public PlayerState
{
private:
	float timeUp = 0;
	float timeDown = 0;
	bool isKicked = false;
	int beginnx = 1;
	float counterTimeFlip = 0;

	bool SetAnotherState = false; //To ignore Stop current update function after set to another state

public:
	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) override;
	virtual Data Exit(Player& player, EPlayerState toState) override;
	virtual void Update(Player& player, float deltaTime) override;
	virtual void HandleKeyboard(Player& player, Keyboard* keyboard) override;
	virtual void OnKeyDown(Player& player, BYTE code) override;
	virtual void OnKeyUp(Player& player, BYTE code) override;
	virtual void OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent) override;

	EPlayerState GetState();
};