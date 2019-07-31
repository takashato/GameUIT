#include "pch.h"
#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState(Player* player) : PlayerState(player)
{
	if (player == nullptr) return;
	player->SetVelocityX(0.0f);
	player->SetVelocityY(0.0f);
}

EPlayerState PlayerStandingState::GetState()
{
	return Standing;
}

void PlayerStandingState::HandleKeyboard(Keyboard* keyboard)
{
	int counter = 0;
	if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mPlayer->AddPositionY(mPlayer->mAniStanding->GetHeight() - mPlayer->mAniRunning->GetHeight());
		mPlayer->SetState(new PlayerRunningState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerJumpingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->AddPositionY(mPlayer->mAniStanding->GetHeight() - mPlayer->mAniSitting->GetHeight());
		mPlayer->SetState(new PlayerSittingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		mPlayer->SetState(new PlayerHighShieldingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		if (mPlayer->GetShield()->IsThrown())
		{
			mPlayer->AddPositionY(mPlayer->mAniStanding->GetHeight() - mPlayer->mAniPunching->GetHeight());
			mPlayer->SetState(new PlayerPunchingState(mPlayer));
		}
		else
		{
			mPlayer->AddPositionY(mPlayer->mAniStanding->GetHeight() - mPlayer->mAniThrowingShield->GetHeight());
			mPlayer->SetState(new PlayerThrowingShieldState(mPlayer));
		}
	}
	else if (keyboard->IsPressing(GAME_KEY_SURF))
	{
		mPlayer->SetState(new PlayerSurfingState(mPlayer));	
	}
	
	/*else
	{
		mPlayer->SetVelocityX(.0f);
	}*/
}