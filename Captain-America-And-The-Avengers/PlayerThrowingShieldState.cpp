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
	if (mPlayer->GetCurrentAnimation()->IsDoneCycle())
	{
		auto player = mPlayer; // Store mPlayer before this->mPlayer gone, lmao
		//if (isHaveShield == false && keyboard->IsPressing(GAME_KEY_ATTACK))
		//{
		//	player->SetState(new PlayerPunchingState(player));
		//}
		//else if (keyboard->IsPressing(GAME_KEY_JUMP))
		//{
		//	player->SetState(new PlayerJumpingState(player));
		//}
		//else if (keyboard->IsPressing(GAME_KEY_DOWN))
		//{
		//	player->SetState(new PlayerSittingState(player));
		//}
		//else if (keyboard->IsPressing(GAME_KEY_UP))
		//{
		//	player->SetState(new PlayerHighShieldingState(player));
		//}
		//else if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
		//{
		//	player->SetState(new PlayerRunningState(player));
		//}
		player->AddPositionY(player->mAniThrowingShield->GetHeight() - player->mAniStanding->GetHeight());
		player->SetState(new PlayerStandingState(player));
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