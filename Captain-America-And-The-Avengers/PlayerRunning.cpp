#include "pch.h"
#include "PlayerRunning.h"
#include "Player.h"

void PlayerRunning::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.SetVelocityY(GRAVITY);
}

Data PlayerRunning::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerRunning::Update(Player& player, float deltaTime)
{
	player.SetVelocityX(player.GetDirection() * WALKING_SPEED);
	player.SetVelocityY(GRAVITY);
}

void PlayerRunning::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		player.SetDirection(EntityDirection::Left);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetDirection(EntityDirection::Right);
	}
}

void PlayerRunning::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
}

void PlayerRunning::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
	{
		player.SetState(EPlayerState::Standing);
	}
}

void PlayerRunning::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerRunning::GetState()
{
	return EPlayerState::Running;
}
