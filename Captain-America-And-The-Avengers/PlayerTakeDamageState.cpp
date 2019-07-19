#include "pch.h"
#include "PlayerTakeDamageState.h"

PlayerTakeDamageState::PlayerTakeDamageState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerTakeDamageState::GetState()
{
	return TakeDamage;
}

void PlayerTakeDamageState::HandleKeyboard(Keyboard* keyboard)
{

}