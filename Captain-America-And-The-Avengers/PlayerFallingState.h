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

	void CheckCollision(std::list<Entity*> entities);

private:
	float mTimeUpdater = .0f;
};