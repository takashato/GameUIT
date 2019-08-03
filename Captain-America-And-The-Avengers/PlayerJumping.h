#pragma once
#include "PlayerState.h"

class PlayerJumping : public PlayerState
{
public:
	virtual void Enter(Player& player, EPlayerState fromState, Data&& data = {}) override;
	virtual Data Exit(Player& player, EPlayerState toState) override;
	virtual void Update(Player& player, float deltaTime) override;
	virtual void HandleKeyboard(Player& player, Keyboard* keyboard) override;
	virtual void OnKeyDown(Player& player, BYTE code) override;
	virtual void OnKeyUp(Player& player, BYTE code) override;
	virtual void OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent) override;

	EPlayerState GetState();

private:
	bool isJumpReleased = false;
	float JumpHeightRealCounter = 0;
	float JumpHeightNeedCounter = MIN_JUMP_HEIGHT;
	bool isKicked = false;

	bool setAnotherState = false;
	bool ignoreUpdate = false;
	float JumpSpeed = JUMP_SPEED_VER_MAX;
};