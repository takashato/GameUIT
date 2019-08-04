#pragma once
#include "PlayerState.h"

class PlayerSitOnShield : public PlayerState
{
	static constexpr auto GRAVITY = 170.0f;
	bool isOnGround = false;

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

