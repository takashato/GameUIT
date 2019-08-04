#include "pch.h"
#include "PlayerStanding.h"
#include "Player.h"

void PlayerStanding::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	if (fromState == EPlayerState::Falling || fromState == EPlayerState::HighJumping)
	{
		SoundManager::GetInstance().CPlaySound(SoundType::TouchTheGround);
	}

	player.SetVelocityX(.0f);
	player.SetVelocityY(GRAVITY);
}

Data PlayerStanding::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerStanding::Update(Player& player, float deltaTime)
{
}

void PlayerStanding::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT) || keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetState(EPlayerState::Running);
	}
	else if (keyboard->IsPressing(GAME_KEY_DOWN))
	{
		player.SetState(EPlayerState::Sitting);
	}
	else if (keyboard->IsPressing(GAME_KEY_UP))
	{
		player.SetState(EPlayerState::HighShielding);
	}
}

void PlayerStanding::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_LEFT || code == VK_RIGHT)
	{
		player.SetState(EPlayerState::Running);
	}
	else if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
	else if (code == VK_DOWN)
	{
		player.SetState(EPlayerState::Sitting);
	}
	else if (code == VK_KEY_ATTACK)
	{
		if (!player.GetShield()->IsThrown())
		{
			player.SetState(EPlayerState::ThrowingShield);
		}
		else
		{
			player.SetState(EPlayerState::Punching);
		}
	}
	else if (code == VK_UP)
	{
		player.SetState(EPlayerState::HighShielding);
	}
}

void PlayerStanding::OnKeyUp(Player& player, BYTE code)
{
}

void PlayerStanding::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform && ce->ny == -1.0f) 
		{
			collisionWithGround = true;
		}
	}
	/*if (!collisionWithGround)
	{
		player.SetState(EPlayerState::Falling);
	}*/
}

EPlayerState PlayerStanding::GetState()
{
	return EPlayerState::Standing;
}
