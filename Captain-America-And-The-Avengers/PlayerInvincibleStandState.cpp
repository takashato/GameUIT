#include "pch.h"
#include "PlayerInvincibleStandState.h"

PlayerInvincibleStandState::PlayerInvincibleStandState(Player* player) : PlayerState(player)
{

}

EPlayerState PlayerInvincibleStandState::GetState()
{
	return InvincibleStand;
}

void PlayerInvincibleStandState::HandleKeyboard(Keyboard* keyboard)
{

}