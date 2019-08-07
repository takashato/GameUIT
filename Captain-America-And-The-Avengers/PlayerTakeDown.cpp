#include "pch.h"
#include "Player.h"
#include "PlayerTakeDown.h"

void PlayerTakeDown::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.mCurrentAni->Reset();
	SoundManager::GetInstance().CPlaySound(SoundType::Death);
	player.SetVelocityX(.0f);
	player.SetVelocityY(.0f);
}

Data PlayerTakeDown::Exit(Player& player, EPlayerState toState)
{
	return std::move(data);
}

void PlayerTakeDown::Update(Player& player, float deltaTime)
{
}

void PlayerTakeDown::HandleKeyboard(Player& player, Keyboard* keyboard)
{
}

void PlayerTakeDown::OnKeyDown(Player& player, BYTE code)
{
	if (code == (BYTE)'R')
	{
		player.mHealth.Set(12);
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerTakeDown::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerTakeDown::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}
