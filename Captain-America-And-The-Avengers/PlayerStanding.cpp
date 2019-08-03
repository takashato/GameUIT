#include "pch.h"
#include "PlayerStanding.h"

void PlayerStanding::Enter(Player& player, EPlayerState fromState, Data&& data)
{
}

Data PlayerStanding::Exit(Player& cap, EPlayerState toState)
{
	return Data();
}

void PlayerStanding::Update(float deltaTime)
{
}

void PlayerStanding::HandleKeyboard(Keyboard* keyboard)
{
}

void PlayerStanding::OnKeyDown(BYTE code)
{
	std::cout << "Standing keydown!!!";
}

void PlayerStanding::OnKeyUp(BYTE code)
{
}

void PlayerStanding::OnCollision(CollisionEvent* ce)
{
}

EPlayerState PlayerStanding::GetState()
{
	return EPlayerState::Standing;
}
