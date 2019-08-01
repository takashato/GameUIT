#include "pch.h"
#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(Player* player) : PlayerState(player)
{
}

void PlayerRunningState::HandleKeyboard(Keyboard* keyboard)
{
	Player* player = mPlayer;
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		player->SetDirection(EntityDirection::Left);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player->SetDirection(EntityDirection::Right);
	}
	
	if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		player->SetState(new PlayerJumpingState(player));
	}
	else if (!keyboard->IsPressing(GAME_KEY_LEFT) && !keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player->AddPositionY(player->mAniRunning->GetHeight() - player->mAniStanding->GetHeight());
		player->SetState(new PlayerStandingState(player));
	}

	
}

void PlayerRunningState::Update(float deltaTime)
{
	if (mPlayer->shouldFall)
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
		return;
	}

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
