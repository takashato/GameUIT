#include "pch.h"
#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(Player* player) : PlayerState(player)
{
}

void PlayerRunningState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		mPlayer->SetDirection(EntityDirection::Left);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mPlayer->SetDirection(EntityDirection::Right);
	}
	else
	{
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}

	if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerJumpingState(mPlayer));
	}
	
}

void PlayerRunningState::Update(float deltaTime)
{
	if (mPlayer->GetDirection() == EntityDirection::Left)
	{
		if (mPlayer->GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
		{
			mPlayer->AddVelocityX(-PLAYER_ACC_X * deltaTime);
			if (mPlayer->GetVelocityX() < -PLAYER_VELOCITY_X_MAX)
				mPlayer->SetVelocityX(-PLAYER_VELOCITY_X_MAX);
		}
	}
	else
	{
		if (mPlayer->GetVelocityX() < PLAYER_VELOCITY_X_MAX)
		{
			mPlayer->AddVelocityX(PLAYER_ACC_X * deltaTime);
			if (mPlayer->GetVelocityX() > PLAYER_VELOCITY_X_MAX)
				mPlayer->SetVelocityX(PLAYER_VELOCITY_X_MAX);
		}
	}
}

EPlayerState PlayerRunningState::GetState()
{
	return EPlayerState::Running;
}
