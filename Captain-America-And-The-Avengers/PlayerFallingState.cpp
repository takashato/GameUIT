#include "pch.h"
#include "PlayerFallingState.h"

PlayerFallingState::PlayerFallingState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(0);
}

void PlayerFallingState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerKickingState(mPlayer));
	}
}

void PlayerFallingState::Update(float deltaTime)
{
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);

	if (mPlayer->GetPosition().y >= 402.0f)
	{
		mPlayer->SetPositionY(402.0f);
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}

EPlayerState PlayerFallingState::GetState()
{
	return EPlayerState::Falling;
}
