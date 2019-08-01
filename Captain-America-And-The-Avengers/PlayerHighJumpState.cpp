#include "pch.h"
#include "PlayerHighJumpState.h"

PlayerHighJumpState::PlayerHighJumpState(Player* player) : PlayerState(player)
{
}


PlayerHighJumpState::~PlayerHighJumpState()
{
}

void PlayerHighJumpState::HandleKeyboard(Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->SetState(new PlayerSittingOnShieldState(mPlayer));
	}
	/*else if (!keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
	}*/
}

void PlayerHighJumpState::Update(float deltaTime)
{
	mTimeUpdater += deltaTime;
	mPlayer->AddVelocityY(PLAYER_GRAVITY * deltaTime);
	if (mTimeUpdater > 0.5f)
	{
		mPlayer->SetState(new PlayerFallingState(mPlayer));
		mTimeUpdater = .0f;
	}
}

EPlayerState PlayerHighJumpState::GetState()
{
	return EPlayerState::HighJumping;
}
