#include "pch.h"
#include "PlayerKickingState.h"

PlayerKickingState::PlayerKickingState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerKickingState::GetState()
{
	return Kicking;
}

void PlayerKickingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}
}