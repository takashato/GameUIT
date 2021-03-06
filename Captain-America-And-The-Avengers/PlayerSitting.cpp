#include "pch.h"
#include "Player.h"
#include "PlayerSitting.h"

void PlayerSitting::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	isPressingKey = false;
	mCounter = .0f;
	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerSitting::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSitting::Update(Player& player, float deltaTime)
{
	if (!isPressingKey)
	{
		mCounter += deltaTime;
		if (mCounter >= FALL_LANDING_TIME)
		{
			mCounter = 0.0f;
			player.SetState(EPlayerState::Standing);
		}
	}
}

void PlayerSitting::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	isPressingKey = keyboard->IsPressing(GAME_KEY_DOWN);
}

void PlayerSitting::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP && isPressingKey)
	{
		player.jumpThrough = true;
		player.SetState(EPlayerState::Falling);
	}
	else if (code == VK_KEY_ATTACK && isPressingKey)
	{
		player.SetState(EPlayerState::LowPunching);
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