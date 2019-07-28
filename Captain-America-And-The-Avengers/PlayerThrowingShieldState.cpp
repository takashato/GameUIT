#include "pch.h"
#include "PlayerThrowingShieldState.h"

PlayerThrowingShieldState::PlayerThrowingShieldState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerThrowingShieldState::GetState()
{
	return ThrowingShield;
}

void PlayerThrowingShieldState::HandleKeyboard(Keyboard* keyboard)
{
	if (isHaveShield == false && keyboard->IsPressing(GAME_KEY_ATTACK))
	{
		mPlayer->SetState(new PlayerPunchingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_JUMP))
	{
		mPlayer->SetState(new PlayerJumpingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		mPlayer->SetState(new PlayerSittingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		mPlayer->SetState(new PlayerHighShieldingState(mPlayer));
	}
	else if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		mPlayer->SetState(new PlayerRunningState(mPlayer));
	}

	if (!keyboard->IsPressing(GAME_KEY_ATTACK)) // This cause access violation, above if conditions may have happened, and mPlayer is inaccessible
	{
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}

void PlayerThrowingShieldState::Update(float deltaTime)
{
	/*mTimeUpdater += deltaTime;
	if (mTimeUpdater >= MOVEMENT_UPDATE_TIME)
	{
		isHaveShield = true;
		mTimeUpdater = .0f;
	}
	else
	{
		isHaveShield = false;
	}*/
}