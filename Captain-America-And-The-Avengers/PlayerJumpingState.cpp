#include "pch.h"
#include "PlayerJumpingState.h"

PlayerJumpingState::PlayerJumpingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(-PLAYER_VELOCITY_Y_MAX);
}

void PlayerJumpingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		mRunState = -1;
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mRunState = 1;
	}
	else
	{
		mRunState = 0;
	}

	Player* player = mPlayer;
	if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		player->SetState(new PlayerKickingState(player));
	}

	if (!keyboard->IsPressing(GAME_KEY_JUMP))
	{
		player->SetState(new PlayerFallingState(player));
	}
}

void PlayerJumpingState::Update(float deltaTime)
{
	mTimeCounter += deltaTime;
	mTimeUpdater += deltaTime;
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
	if (mTimeCounter >= 0.3f && mTimeCounter <= 0.5f)
	{
		mPlayer->SetState(new PlayerHighJumpState(mPlayer));
	}
	else if (mTimeCounter > 0.5f)
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}
	else 
	{
		if (mRunState == -1)
		{
			if (mPlayer->GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(-PLAYER_ACC_X * deltaTime);
				if (mPlayer->GetVelocityX() < -PLAYER_VELOCITY_X_MAX)
					mPlayer->SetVelocityX(-PLAYER_VELOCITY_X_MAX);
			}
		}
		else if (mRunState == 1)
		{
			if (mPlayer->GetVelocityX() < PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(PLAYER_ACC_X * deltaTime);
				if (mPlayer->GetVelocityX() > PLAYER_VELOCITY_X_MAX)
					mPlayer->SetVelocityX(PLAYER_VELOCITY_X_MAX);
			}
		}
		else
		{
			if (mPlayer->GetVelocityX() > .0f)
			{
				mPlayer->AddVelocityX(-PLAYER_ACC_X * deltaTime);
			}
			else
			{
				mPlayer->AddVelocityX(PLAYER_ACC_X * deltaTime);
			}
		}
	}
}

EPlayerState PlayerJumpingState::GetState()
{
	return EPlayerState::Jumping;
}
