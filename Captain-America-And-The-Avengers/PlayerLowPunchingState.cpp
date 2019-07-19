#include "pch.h"
#include "PlayerLowPunchingState.h"

PlayerLowPunchingState::PlayerLowPunchingState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerLowPunchingState::GetState()
{
	return LowPunching;
}

void PlayerLowPunchingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerSittingState(mPlayer));
	}
}