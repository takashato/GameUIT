#include "pch.h"
#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityX(.0f);
	mPlayer->SetVelocityY(.0f);
}

EPlayerState PlayerSittingState::GetState()
{
	return Sitting;
}

void PlayerSittingState::HandleKeyboard(Keyboard* keyboard)
{
	if (mPlayer->GetLastState() != Falling) {
		if (keyboard->IsPressing(GAME_KEY_JUMP))
		{
			mPlayer->SetState(new PlayerJumpingState(mPlayer));
		}
		else if (keyboard->IsPressing(GAME_KEY_ATTACK))
		{
			mPlayer->SetState(new PlayerLowPunchingState(mPlayer));
		}

		if (!keyboard->IsPressing(GAME_KEY_DOWN))
		{
			mPlayer->AddPositionY(mPlayer->mAniSitting->GetHeight() - mPlayer->mAniStanding->GetHeight());
			mPlayer->SetState(new PlayerStandingState(mPlayer));
		}
	}
}

void PlayerSittingState::Update(float deltaTime)
{
	mCounter += deltaTime;
	if (mPlayer->GetLastState() == Falling)
	{
		if (mCounter >= 0.3f)
		{
			mPlayer->AddPositionY(mPlayer->mAniSitting->GetHeight() - mPlayer->mAniStanding->GetHeight());
			mPlayer->SetState(new PlayerStandingState(mPlayer));
		}
	}
}
