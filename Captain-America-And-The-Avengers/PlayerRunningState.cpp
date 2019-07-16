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
	mTimeUpdater += deltaTime;
	if (mTimeUpdater >= MOVEMENT_UPDATE_TIME)
	{
		if (mPlayer->GetDirection() == EntityDirection::Left)
		{
			if (mPlayer->GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(-PLAYER_ACC_X);
			}
		}
		else
		{
			if (mPlayer->GetVelocityX() < PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(PLAYER_ACC_X);
			}
		}
		mTimeUpdater = .0f;
	}
}

EPlayerState PlayerRunningState::GetState()
{
	return EPlayerState::Running;
}
