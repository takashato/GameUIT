#include "pch.h"
#include "PlayerHighJumpState.h"

PlayerHighJumpState::PlayerHighJumpState(Player* player) : PlayerState(player)
{
}


PlayerHighJumpState::~PlayerHighJumpState()
{
}

void PlayerHighJumpState::HandleKeyboard(Keyboard* keyboard)
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

	if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->SetState(new PlayerSittingOnShieldState(mPlayer));
	}
	/*else if (!keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}*/
}

void PlayerHighJumpState::Update(float deltaTime)
{
	mTimeUpdater += deltaTime;
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
	if (mTimeUpdater > 0.5f)
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
		mTimeUpdater = .0f;
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

EPlayerState PlayerHighJumpState::GetState()
{
	return EPlayerState::HighJumping;
}
