#pragma once
#include "PlayerState.h"

class PlayerKicking : public PlayerState
{
private:
	EPlayerState lastState;
	bool isJumpReleased;
	float JumpHeightRealCounter;
	float JumpHeightNeedCounter;
	float timeUp = 0;
	float timeDown = 0;
	bool isKicked = true;

	bool SetAnotherState = false; //To end Update after Handle collision

	bool firstTimeUpdate = true;
public:
	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) override;
	virtual Data Exit(Player& cap, EPlayerState toState) override;
	virtual void Update(Player& player, float deltaTime) override;
	virtual void HandleKeyboard(Player& player, Keyboard* keyboard) override;
	virtual void OnKeyDown(Player& player, BYTE code) override;
	virtual void OnKeyUp(Player& player, BYTE code) override;
	virtual void OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent) override;
	EPlayerState GetState();
};

