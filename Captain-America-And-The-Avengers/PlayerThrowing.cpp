#include "pch.h"
#include "PlayerThrowing.h"
#include "Player.h"

void PlayerThrowing::Enter(Player& player, EPlayerState fromState, Data&& data)
{
}

Data PlayerThrowing::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerThrowing::Update(Player& player, float deltaTime)
{
	if (player.GetCurrentAnimation()->IsDoneCycle())
	{
		player.GetShield()->Throw();
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerThrowing::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerThrowing::OnKeyDown(Player& player, BYTE code)
{
}

void PlayerThrowing::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerThrowing::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerThrowing::GetState()
{
	return EPlayerState::ThrowingShield;
}
