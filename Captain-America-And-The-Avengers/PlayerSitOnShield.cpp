#include "pch.h"
#include "Player.h"
#include "PlayerSitOnShield.h"

void PlayerSitOnShield::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	assert(fromState == EPlayerState::HighJumping);
	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
	bool isOnGround = false;
}

Data PlayerSitOnShield::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSitOnShield::Update(Player& player, float deltaTime)
{
	
}

void PlayerSitOnShield::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(-MOVING_HOR);
			player.SetDirection((EntityDirection)-1);
		}
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		if (player.GetVelocityX() >= 0)
		{
			player.SetVelocityX(MOVING_HOR);
			player.SetDirection((EntityDirection)1);
		}
	}
}

void PlayerSitOnShield::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_ATTACK)
	{
		if (isOnGround)
			player.SetState(EPlayerState::LowPunching);
		else
			player.SetState(EPlayerState::Kicking);
	}
}

void PlayerSitOnShield::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_DOWN)
	{
		if(isOnGround)
			player.SetState(EPlayerState::Standing);
		else
			player.SetState(EPlayerState::Falling);
	}
}

void PlayerSitOnShield::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
}

EPlayerState PlayerSitOnShield::GetState()
{
	return EPlayerState::SittingOnShield;
}