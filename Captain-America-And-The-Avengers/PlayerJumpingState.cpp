#include "pch.h"
#include "PlayerJumpingState.h"

PlayerJumpingState::PlayerJumpingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(-PLAYER_VELOCITY_Y_MAX);
}

void PlayerJumpingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerKickingState(mPlayer));
	}

	if (!keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}
}

void PlayerJumpingState::Update(float deltaTime)
{
	mTimeCounter += deltaTime;
	mTimeUpdater += deltaTime;
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
	if (mTimeCounter >= 0.3f && mTimeCounter <= 0.5f)
		mPlayer->SetState(new PlayerHighJumpState(mPlayer));
	if (mTimeCounter > 0.5f)
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}
}

EPlayerState PlayerJumpingState::GetState()
{
	return EPlayerState::Jumping;
}
