#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerKickingState.h"

class PlayerFallingState : public PlayerState
{
public:
	PlayerFallingState(Player* player);

	void HandleKeyboard(Keyboard* keyboard);
	void Update(float deltaTime);

	EPlayerState GetState();

	void OnCollision(CollisionEvent* ce);

private:
	float mTimeUpdater = .0f;
};