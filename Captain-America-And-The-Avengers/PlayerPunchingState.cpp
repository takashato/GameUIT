#include "pch.h"
#include "PlayerPunchingState.h"


PlayerPunchingState::PlayerPunchingState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerPunchingState::GetState()
{
	return Punching;
}

void PlayerPunchingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}