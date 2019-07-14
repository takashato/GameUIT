#include "pch.h"
#include "PlayerStandingState.h"

PlayerStandingState::PlayerStandingState(Player* player) : PlayerState(player)
{
	player->SetVelocityX(0.0f);
	player->SetVelocityY(0.0f);
}

EPlayerState PlayerStandingState::GetState()
{
	return Standing;
}

void PlayerStandingState::HandleKeyboard(Keyboard& keyboard)
{
	if (keyboard.IsPressing(VK_LEFT) || keyboard.IsPressing(VK_RIGHT))
	{
		mPlayer->SetState(new PlayerRunningState(mPlayer));
	}
}
