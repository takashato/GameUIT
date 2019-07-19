#include "pch.h"
#include "PlayerClingState.h"

PlayerClingState::PlayerClingState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerClingState::GetState()
{
	return Cling;
}

void PlayerClingState::HandleKeyboard(Keyboard* keyboard)
{

}