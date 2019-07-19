#include "pch.h"
#include "PlayerSwimmingState.h"

PlayerSwimmingState::PlayerSwimmingState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerSwimmingState::GetState()
{
	return Swimming;
}

void PlayerSwimmingState::HandleKeyboard(Keyboard* keyboard)
{

}