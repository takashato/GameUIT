#include "pch.h"
#include "Player.h"
#include "PlayerSitting.h"

void PlayerSitting::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerSitting::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSitting::Update(Player& player, float deltaTime)
{
}

void PlayerSitting::HandleKeyboard(Player& player, Keyboard* keyboard)
{

}

void PlayerSitting::OnKeyDown(Player& player, BYTE code)
{

}

void PlayerSitting::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_DOWN)
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerSitting::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerSitting::GetState()
{
	return EPlayerState::Sitting;
}