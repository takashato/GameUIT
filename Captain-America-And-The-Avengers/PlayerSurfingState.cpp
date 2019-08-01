#include "pch.h"
#include "PlayerSurfingState.h"

PlayerSurfingState::PlayerSurfingState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerSurfingState::GetState()
{
	return Surfing;
}

void PlayerSurfingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_SURF))
	{
		mPlayer->AddPositionY(mPlayer->mAniSurfing->GetHeight() - mPlayer->mAniStanding->GetHeight());
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}

void PlayerSurfingState::Update(float deltaTime)
{
	mTimeUpdater += deltaTime;
	if (mTimeUpdater >= MOVEMENT_UPDATE_TIME)
	{
		if (mPlayer->GetDirection() == EntityDirection::Left)
		{
			if (mPlayer->GetVelocityX() > -PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(-2*PLAYER_ACC_X);
			}
		}
		else
		{
			if (mPlayer->GetVelocityX() < PLAYER_VELOCITY_X_MAX)
			{
				mPlayer->AddVelocityX(2*PLAYER_ACC_X);
			}
		}
		mTimeUpdater = .0f;
	}
}