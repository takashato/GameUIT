#include "pch.h"
#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerSittingState::GetState()
{
	return Sitting;
}

void PlayerSittingState::HandleKeyboard(Keyboard* keyboard)
{
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
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}