#include "pch.h"
#include "Player.h"
#include "PlayerLowPunching.h"

void PlayerLowPunching::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	SoundManager::GetInstance().CPlaySound(SoundType::Hit);

	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerLowPunching::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerLowPunching::Update(Player& player, float deltaTime)
{
	if (player.GetCurrentAnimation()->IsDoneCycle())
	{
		player.SetState(EPlayerState::Sitting);
	}
}

void PlayerLowPunching::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerLowPunching::OnKeyDown(Player& player, BYTE code)
{
	
}

void PlayerLowPunching::OnKeyUp(Player& player, BYTE code)
{
	
}

void PlayerLowPunching::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerLowPunching::GetState()
{
	return EPlayerState::LowPunching;
}