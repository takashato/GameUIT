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

}