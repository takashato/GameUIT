#include "pch.h"
#include "PlayerTakeDownState.h"

PlayerTakeDownState::PlayerTakeDownState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerTakeDownState::GetState()
{
	return TakeDown;
}

void PlayerTakeDownState::HandleKeyboard(Keyboard* keyboard)
{

}