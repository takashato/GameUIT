#include "pch.h"
#include "PlayerSittingOnShieldState.h"

PlayerSittingOnShieldState::PlayerSittingOnShieldState(Player* player) : PlayerState(player)
{
	mPlayer->SetVelocityY(0);
}

EPlayerState PlayerSittingOnShieldState::GetState()
{
	return SittingOnShield;
}

void PlayerSittingOnShieldState::Update(float deltaTime)
{
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
}

void PlayerSittingOnShieldState::HandleKeyboard(Keyboard* keyboard)
{
	if (!keyboard->IsPressing(GAME_KEY_DOWN))
		mPlayer->SetState(new PlayerFallingState(mPlayer));
}