#include "pch.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(0);
}

void PlayerFallingState::HandleKeyboard(Keyboard* keyboard)
{
}

void PlayerFallingState::Update(float deltaTime)
{
	mTimeUpdater += deltaTime;
	if (deltaTime >= MOVEMENT_UPDATE_TIME) {
		mPlayer->AddVelocityY(PLAYER_GRAVITY);
		mTimeUpdater = .0f;
	}
	if (mPlayer->GetPosition().y >= 411.0f)
	{
		mPlayer->SetPositionY(411.0f);
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}

EPlayerState PlayerFallingState::GetState()
{
	return EPlayerState::Falling;
}
