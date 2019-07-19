#include "pch.h"
#include "PlayerSittingOnShieldState.h"

PlayerSittingOnShieldState::PlayerSittingOnShieldState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerSittingOnShieldState::GetState()
{
	return SittingOnShield;
}

void PlayerSittingOnShieldState::HandleKeyboard(Keyboard* keyboard)
{

}