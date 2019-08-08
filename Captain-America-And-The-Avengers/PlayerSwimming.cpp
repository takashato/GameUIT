#include "pch.h"
#include "Player.h"
#include "Ground.h"
#include "PlayerSwimming.h"

void PlayerSwimming::Enter(Player& player, EPlayerState fromState, Data&& data)
{
	player.ChangeAnimationByState(EPlayerState::Swimming);
}

Data PlayerSwimming::Exit(Player& player, EPlayerState toState)
{
	return Data();
}

void PlayerSwimming::Update(Player& player, float deltaTime)
{
}

void PlayerSwimming::HandleKeyboard(Player& player, Keyboard* keyboard)
{
	if (keyboard->IsPressing(GAME_KEY_LEFT))
	{
		player.SetDirection(EntityDirection::Left);
		player.SetVelocityX(-SWIMMING_SPEED + WATER_FLOW_SPEED);
	}
	else if (keyboard->IsPressing(GAME_KEY_RIGHT))
	{
		player.SetDirection(EntityDirection::Right);
		player.SetVelocityX(SWIMMING_SPEED + WATER_FLOW_SPEED);
	}
	else
	{
		player.SetVelocityX(WATER_FLOW_SPEED);
	}
}

void PlayerSwimming::OnKeyDown(Player& player, BYTE code)
{
	if (code == VK_KEY_JUMP)
	{
		player.SetState(EPlayerState::Jumping);
	}
	else if (code == VK_DOWN)
	{
		player.ChangeAnimationByState(EPlayerState::Diving);
	}
}

void PlayerSwimming::OnKeyUp(Player& player, BYTE code)
{
	if (code == VK_DOWN)
	{
		player.ChangeAnimationByState(EPlayerState::Swimming);
	}
}

void PlayerSwimming::OnCollision(Player& player, std::vector<CollisionEvent*>& cEvent)
{
	bool collisionWithGround = false;
	for (auto ce : cEvent)
	{
		if (ce->entity->GetCollidableObjectType() == EPlatform)
		{
			if (ce->ny == -1.0f)
			{
				collisionWithGround = true;
			}

			if (((Ground*)ce->entity)->GetGroundType() == EGroundHard)
			{
				if (ce->nx == -1.0f)
				{
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetPosition().x - (player.GetWidth() / 2 + Player::PLAYER_HITBOX_HALF));
				}
				else if (ce->nx == 1.0f)
				{
					player.SetVelocityX(.0f);
					player.SetPositionX(ce->entity->GetBoundingBox().right + (player.GetWidth() / 2 - Player::PLAYER_HITBOX_HALF));
				}
			}
		}

	}
	if (!collisionWithGround)
	{
		player.SetState(EPlayerState::Falling);
	}
}

EPlayerState PlayerSwimming::GetState()
{
	return EPlayerState::Swimming;
}
