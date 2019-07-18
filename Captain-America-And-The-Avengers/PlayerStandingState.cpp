#include "pch.h"
#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState(Player* player) : PlayerState(player)
{
	player->SetVelocityX(0.0f);
	player->SetVelocityY(0.0f);
}

EPlayerState PlayerStandingState::GetState()
{
	return Standing;
}

void PlayerStandingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mPlayer->SetState(new PlayerRunningState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerJumpingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->SetState(new PlayerSittingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		mPlayer->SetState(new PlayerHighShieldingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerPunchingState(mPlayer));
	}
	
	/*else
	{
		mPlayer->SetVelocityX(.0f);
	}*/
}
