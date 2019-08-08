#include "pch.h"
#include "Player.h"
#include "PlayerCling.h"

void PlayerCling::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	if (fromState == EPlayerState::Falling)
	{
		SoundManager::GetInstance().CPlaySound(SoundType::TouchTheGround);
	}

	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerCling::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerCling::Update(Player& player, float deltaTime)
{
}

void PlayerCling::HandleKeyboard(Player& player, Keyboard* keyboard)
{

}

void PlayerCling::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
	else if (code == VK_DOWN)
	{
		player.SetState(EPlayerState::Falling);
	}
	else if (code == VK_LEFT)
	{
		if (player.GetDirection() == Right)
			player.SetDirection(Left);

	}
	else if (code == VK_RIGHT)
	{
		if (player.GetDirection() == Left)
			player.SetDirection(Right);
	}
}

void PlayerCling::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerCling::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	
}

EPlayerState PlayerCling::GetState()
{
	return EPlayerState::Cling;
}