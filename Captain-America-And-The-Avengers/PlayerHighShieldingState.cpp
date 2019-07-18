#include "pch.h"
#include "PlayerHighShieldingState.h"

PlayerHighShieldingState::PlayerHighShieldingState(Player* player) : PlayerState(player)
{
	player->SetVelocityX(0.0f);
	player->SetVelocityY(0.0f);
}

EPlayerState PlayerHighShieldingState::GetState()
{
	return HighShielding;
}

void PlayerHighShieldingState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_UP))
	{
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}