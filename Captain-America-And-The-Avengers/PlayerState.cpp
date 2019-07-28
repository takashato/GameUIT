#include "pch.h"
#include "PlayerState.h"

PlayerState::PlayerState(Player* player)
{
	mPlayer = player;
}

Player* PlayerState::GetPlayer()
{
	return mPlayer;
}

void PlayerState::Update(float deltaTime)
{
}

EPlayerState PlayerState::GetState()
{
	return EPlayerState::Running;
}

void PlayerState::HandleKeyboard(Keyboard* keyboard)
{
}

void PlayerState::OnCollision(CollisionEvent* ce)
{
}
