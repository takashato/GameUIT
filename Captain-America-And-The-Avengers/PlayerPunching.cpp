#include "pch.h"
#include "Player.h"
#include "PlayerPunching.h"

void PlayerPunching::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	SoundManager::GetInstance().CPlaySound(SoundType::Hit);

	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerPunching::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerPunching::Update(Player& player, float deltaTime)
{
	if (player.GetCurrentAnimation()->IsDoneCycle() || !player.GetShield()->IsThrown())
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerPunching::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerPunching::OnKeyDown(Player& player, BYTE code)
{

}

void PlayerPunching::OnKeyUp(Player& player, BYTE code)
{

}

void PlayerPunching::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerPunching::GetState()
{
	return EPlayerState::Punching;
}