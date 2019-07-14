#include "pch.h"
#include "PlayerRunningState.h"

PlayerRunningState::PlayerRunningState(Player* player) : PlayerState(player)
{
	mAcceleratorX = 25.0f;
}

void PlayerRunningState::HandleKeyboard(Keyboard& keyboard)
{
	if (keyboard.IsPressing(VK_LEFT))
	{
		mPlayer->SetDirection(EntityDirection::Left);
	}
	else if (keyboard.IsPressing(VK_RIGHT))
	{
		mPlayer->SetDirection(EntityDirection::Right);
	}
	else
	{
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}

EPlayerState PlayerRunningState::GetState()
{
	return EPlayerState::Running;
}
