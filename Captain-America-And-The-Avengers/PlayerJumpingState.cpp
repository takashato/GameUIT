#include "pch.h"
#include "PlayerJumpingState.h"

PlayerJumpingState::PlayerJumpingState(Player* player) : PlayerState(player)
{
	// accelector
}

void PlayerJumpingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_JUMP))
	{
		if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
		{
			mPlayer->SetState(new PlayerRunningState(mPlayer));
		}
		else
		{
			mPlayer->SetState(new PlayerStandingState(mPlayer));
		}
	}
}

EPlayerState PlayerJumpingState::GetState()
{
	return EPlayerState::Jumping;
}
