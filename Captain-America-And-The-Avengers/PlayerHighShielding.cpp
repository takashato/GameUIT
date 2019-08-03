#include "pch.h"
#include "Player.h"
#include "PlayerHighShielding.h"

void PlayerHighShielding::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerHighShielding::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerHighShielding::Update(Player& player, float deltaTime)
{
}

void PlayerHighShielding::HandleKeyboard(Player& player, Keyboard* keyboard)
{

}

void PlayerHighShielding::OnKeyDown(Player& player, BYTE code)
{

}

void PlayerHighShielding::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_UP)
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerHighShielding::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerHighShielding::GetState()
{
	return EPlayerState::HighShielding;
}