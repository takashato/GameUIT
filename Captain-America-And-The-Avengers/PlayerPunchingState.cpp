#include "pch.h"
#include "PlayerPunchingState.h"
#include "Shield.h"

PlayerPunchingState::PlayerPunchingState(Player* player) : PlayerState(player)
{
}

EPlayerState PlayerPunchingState::GetState()
{
	return Punching;
}

void PlayerPunchingState::HandleKeyboard(Keyboard* keyboard)
{
	if (mPlayer->GetCurrentAnimation()->IsDoneCycle() || !mPlayer->GetShield()->IsThrown())
	{
		mPlayer->AddPositionY(mPlayer->mAniPunching->GetHeight() - mPlayer->mAniStanding->GetHeight());
		mPlayer->SetState(new PlayerStandingState(mPlayer));
	}
}